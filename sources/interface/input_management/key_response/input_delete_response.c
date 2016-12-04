/*
** input_delete_response.c for PSU_2015_42sh in sources/ncurses/input_management/key_response
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:26:32 2016 Nicolas Goudal
** Last update Thu Dec 01 11:01:44 2016
*/

#include <string.h>
#include "interface/interface_private.h"
#include "interface/input_private.h"

/*
** delete the character in 'read_buf->cmd' positioned before the cursor
*/
t_istatus		input_delete_response(t_interface *interface)
{
  int		i;

  if (!!input_move_completion(interface))
    return (S_SUCCESS);
  i = interface->read_buf.cmd.idx + interface->read_buf.cursor.x;
  if (i > 0)
  {
    --interface->read_buf.cmd.idx;
    memmove(interface->read_buf.cmd.buf + i - 1,
	    interface->read_buf.cmd.buf + i,
	    -interface->read_buf.cursor.x);
    interface->read_buf.cmd.buf[interface->read_buf.cmd.idx] = '\0';
  }
  return (S_SUCCESS);
}

/*
** delete the character in 'read_buf->cmd' positioned on the cursor
*/
t_istatus		input_suppr_response(t_interface *interface)
{
  int		i;

  if (!!input_move_completion(interface)
      || interface->read_buf.cursor.x >= 0)
    return (S_SUCCESS);
  i = interface->read_buf.cmd.idx + interface->read_buf.cursor.x;
  ++interface->read_buf.cursor.x;
  if (i > 0)
  {
    --interface->read_buf.cmd.idx;
    while (i < interface->read_buf.cmd.idx)
    {
      interface->read_buf.cmd.buf[i] = interface->read_buf.cmd.buf[i + 1];
      ++i;
    }
    interface->read_buf.cmd.buf[interface->read_buf.cmd.idx] = '\0';
  }
  return (S_SUCCESS);
}
