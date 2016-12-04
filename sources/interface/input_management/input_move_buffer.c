/*
** input_move_buffer.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:25:45 2016 Nicolas Goudal
** Last update Sat Dec 03 13:15:47 2016 Benoit Hamon
*/

#include <string.h>
#include "interface/interface_private.h"
#include "interface/input_private.h"
#include "interface/interface_complete.h"

t_istatus		input_move_line_completion(t_interface *interface)
{
  if (interface->read_buf.completion.type != LINE_COMPL)
    return (S_SUCCESS);
  if (!!(increase_buffer_size(&interface->read_buf.cmd, I_BUF_SIZE,
			      interface->read_buf.cmd.idx
			      + interface->read_buf.completion.len)))
    return (S_FAILURE);
  (void)strncpy(interface->read_buf.cmd.buf + interface->read_buf.cmd.idx,
		interface->read_buf.completion.aff,
		interface->read_buf.completion.aff_len);
  interface->read_buf.cmd.idx += interface->read_buf.completion.len;
  interface->read_buf.cursor.x = 0;
  memset(&interface->read_buf.completion, 0, sizeof(t_cmd_completion));
  return (S_SUCCESS);
}

/*
** move completion into command buffer
*/
t_istatus		input_move_completion(t_interface *interface)
{
  if (interface->read_buf.completion.type != HISTO_COMPL)
    return (S_SUCCESS);
  if (!!(increase_buffer_size(&interface->read_buf.cmd, I_BUF_SIZE,
			      interface->read_buf.cmd.idx
			      + interface->read_buf.completion.len)))
    return (S_FAILURE);
  (void)strncpy(interface->read_buf.cmd.buf,
		interface->read_buf.completion.str,
		interface->read_buf.completion.len + 1);
  interface->read_buf.cmd.idx = interface->read_buf.completion.len;
  interface->historic.selected = NULL;
  memset(&interface->read_buf.completion, 0, sizeof(t_cmd_completion));
  return (S_SUCCESS);
}

/*
** concat 'src' buffer into 'dest' buffer
** if needef 'dest' buffer size will be increased
** 'src' buffer is then cleaned
** return 1 on succes
** return 0 in case the increase of 'dest' buffer failed
*/
t_istatus		input_cat_buffer(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term)
{
  int			i;
  t_read_buf		*read_buf;

  (void)c;
  (void)term;
  *status = S_FAILURE;
  read_buf = &interface->read_buf;
  if (!!input_move_completion(interface)
      || !!increase_buffer_size(&read_buf->cmd, I_BUF_SIZE,
				read_buf->cmd.idx + read_buf->input.idx))
    return (S_STOP);
  i = read_buf->cmd.idx + read_buf->cursor.x;
  if (read_buf->cursor.x)
    memmove(read_buf->cmd.buf + i + read_buf->input.idx,
	    read_buf->cmd.buf + i,
	    -interface->read_buf.cursor.x);
  strncpy(read_buf->cmd.buf + i, read_buf->input.buf, read_buf->input.idx);
  read_buf->cmd.idx += read_buf->input.idx;
  memset(read_buf->input.buf, 0, read_buf->input.idx);
  read_buf->input.idx = 0;
  return (S_SUCCESS);
}
