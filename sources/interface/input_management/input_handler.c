/*
** input_handler.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:24:20 2016 Nicolas Goudal
** Last update Thu Dec 01 11:01:05 2016
*/

#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include "interface/interface_private.h"

/*
** increase buf buffer size by 'inc_size'
** the added part is filled with 0
** return S_SUCESS on success
** return S_FAILURE if malloc failed
*/
t_istatus		increase_buffer_size(t_buffer *buf,
					     int inc_size,
					     int min_size)
{
  char			*buffer;

  while (buf->size < min_size)
  {
    buf->size += inc_size;
    if (!(buffer = malloc(sizeof(char) * (buf->size + 1))))
      return (S_FAILURE);
    (void)memset(buffer, 0, sizeof(char) * (buf->size + 1));
    (void)strncpy(buffer, buf->buf, buf->size - inc_size);
    free(buf->buf);
    buf->buf = buffer;
  }
  return (S_SUCCESS);
}

/*
** Compare 's1' and 's2'
*/
static int		start_cmp(char const *s1,
				  char const *s2)
{
  int			i;

  i = 0;
  if (!s1 || !s2)
    return (CMP_DIFFERENT);
  while (s1[i] && s2[i] && s1[i] == s2[i])
    ++i;
  if (!i || s1[i])
    return (CMP_DIFFERENT);
  else if (s2[i])
    return (CMP_SEEMS);
  return (CMP_CORRESPOND);
}

static t_istatus	input_handle_cmp_value(t_startcmp_value cmp_value,
					       t_istatus *status,
					       t_interface *interface,
					       int idx)
{
  if (cmp_value == CMP_SEEMS)
    *status = S_SUCCESS;
  else if (cmp_value == CMP_CORRESPOND)
  {
    if (interface->esc_seq.input[idx].response)
      interface->esc_seq.input[idx].response(interface);
    memset(interface->read_buf.input.buf, 0, interface->read_buf.input.size);
    interface->read_buf.input.idx = 0;
    return (S_SUCCESS);
  }
  return (S_FAILURE);
}

/*
** check if 'input' buffer size shall be increased
** increase its size if needed
** add c to 'input' buffer
** if 'input' buffer correspond to elem of 'esc_seq_list'
** the corresponding action is taken and 'input' buffer is cleaned
** if 'input' buffer doesn't seem to correspond it is concatened into
** 'cmd' buffer and cleaned
*/
t_istatus		input_is_esc_seq(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term)
{
  t_istatus		state;
  t_startcmp_value	cmp_value;
  int			i;

  (void)term;
  if (!!increase_buffer_size(&interface->read_buf.input, I_INP_SIZE,
			     interface->read_buf.input.idx + 1))
    return (S_STOP);
  interface->read_buf.input.buf[interface->read_buf.input.idx] = c;
  ++interface->read_buf.input.idx;
  *status = S_FAILURE;
  state = S_FAILURE;
  i = -1;
  while (++i < ESIN_END)
  {
    cmp_value = start_cmp(interface->read_buf.input.buf,
			  interface->esc_seq.input[i].seq);
    if (input_handle_cmp_value(cmp_value, &state, interface,
			       i) == S_SUCCESS)
      return (S_SUCCESS);
  }
  return (state);
}
