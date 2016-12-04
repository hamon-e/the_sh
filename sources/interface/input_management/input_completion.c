/*
** input_completion.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:23:54 2016 Nicolas Goudal
** Last update Sun Dec 04 16:58:27 2016 Benoit Hamon
*/

#include "interface/interface_private.h"
#include "interface/input_private.h"

void		completion_get_next(t_completion_buf *buf)
{
  if (!buf->selected || !buf->selected->next)
    buf->selected = buf->list;
  else
    buf->selected =  buf->selected->next;
}

t_istatus	input_completion_response(t_interface *interface)
{
  t_return	graph;
  int		i;

  if (!interface->read_buf.completion.comp.list)
  {
    graph = launch_parser(interface->lexer, interface->read_buf.cmd.buf, &i);
    interface_init_completion(interface, graph.graph);
  }
  else
    completion_get_next(&interface->read_buf.completion.comp);
  return (S_SUCCESS);
}
