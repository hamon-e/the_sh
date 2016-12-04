/*
** input.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:23:44 2016 Nicolas Goudal
** Last update Sat Dec 03 13:53:01 2016 Benoit Hamon
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "interface/input_private.h"
#include "interface/interface_complete.h"

static void		input_insert(t_interface *interface)
{
  t_completion_buf	*comp;
  t_buffer		*cmd;
  int			len;
  int			i;

  comp = &interface->read_buf.completion.comp;
  cmd = &interface->read_buf.cmd;
  i = 0;
  while (cmd->idx - i && cmd->buf[cmd->idx - i - 1] != ' ')
    ++i;
  if (!comp->selected)
    return ;
  if (!!increase_buffer_size(cmd, I_BUF_SIZE,
			     cmd->idx + comp->selected->length))
    return ;
  if ((len = cmd->idx - comp->idx - comp->len) > 0)
    memmove(cmd->buf + comp->idx + comp->selected->length,
	    cmd->buf + comp->idx + comp->len,
	    cmd->idx - comp->idx - comp->len);
  else
    cmd->idx += -len;
  cmd->idx += (comp->selected->length - comp->len - i);
  strncpy(cmd->buf + comp->idx - i, comp->selected->str,
	  comp->selected->length);
  interface->read_buf.cursor.x = 0;
}

/*
** check if it is the end of a command line
*/
t_istatus		input_is_cmd_end(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term)
{
  (void)interface;
  (void)c;
  (void)term;
  if (c != '\n' || (interface->read_buf.cmd.idx
		    && interface->read_buf.cmd.buf
		    [interface->read_buf.cmd.idx - 1] == '\\'
		    && !interface->read_buf.cursor.x))
    return (S_FAILURE);
  if (interface->read_buf.completion.comp.list)
  {
    input_insert(interface);
    interface->read_buf.completion.comp.list = NULL;
    interface->read_buf.completion.comp.selected = NULL;
    return (S_SUCCESS);
  }
  input_move_completion(interface);
  *status = S_SUCCESS;
  return (S_SUCCESS);
}

/*
** read 1 char of stdin
** add it to 'read_buf->input'
** check if it correspond to a element of 'esc_seq_list'
** if it is the corresponding action is taken
** else it is concated to 'read_buf->input'
** return S_SUCCESS if nothing went wrong
** return S_FAILURE in case the concatening failed
*/
t_istatus			input_read(t_interface *interface)
{
  char				c;
  t_istatus			status;
  int				i;
  static t_input_handler	input_handler[] =
  {
    input_is_special_char,
    input_is_cmd_end,
    input_is_esc_seq,
    input_cat_buffer,
    NULL
  };

  if (read(0, &c, 1) <= 0)
    return (S_FAILURE);
  i = 0;
  status = S_FAILURE;
  while (input_handler[i]
	 && status == S_FAILURE)
  {
    if (input_handler[i](interface, c, &status, &interface->term)
	!= S_FAILURE)
      return (status);
    ++i;
  }
  return (status);
}
