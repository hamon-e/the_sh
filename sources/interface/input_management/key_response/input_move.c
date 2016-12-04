/*
** input_move.c for PSU_2015_42sh in sources/ncurses/input_management/key_response
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:27:14 2016 Nicolas Goudal
** Last update Sun Dec 04 16:58:16 2016 Benoit Hamon
*/

#include <stdbool.h>
#include "the_parser/parser.h"
#include "interface/interface.h"
#include "interface/interface_complete.h"
#include "interface/input_private.h"

static void	launch_completion(t_interface *interface)
{
  t_return	graph;
  int		i;

  if (interface->read_buf.completion.comp.list)
  {
    graph = launch_parser(interface->lexer, interface->read_buf.cmd.buf, &i);
    interface_init_completion(interface, graph.graph);
  }
}

/*
** move the cursor to the right
*/
t_istatus	input_right_arrow_response(t_interface *interface)
{
  if (interface->read_buf.completion.type == LINE_COMPL
      && !interface->read_buf.cursor.x)
    input_move_line_completion(interface);
  if (!interface->read_buf.completion.str
      && interface->read_buf.cursor.x < 0)
  {
    ++interface->read_buf.cursor.x;
    while (interface->read_buf.cursor.x < 0
	   && interface->read_buf.cmd.buf[interface->read_buf.cmd.idx
	   + interface->read_buf.cursor.x]
	   == '\n')
      ++interface->read_buf.cursor.x;
  }
  else if (interface->read_buf.completion.str
	   && interface->read_buf.cursor.x < 0)
  {
    ++interface->read_buf.cursor.x;
    while (interface->read_buf.cursor.x < 0
	   && interface->read_buf.completion.str
	   [interface->read_buf.completion.len + interface->read_buf.cursor.x]
	   == '\n')
      ++interface->read_buf.cursor.x;
  }
  launch_completion(interface);
  return (S_SUCCESS);
}

/*
** move the cursor to the left
*/
t_istatus	input_left_arrow_response(t_interface *interface)
{
  if (!(interface->read_buf.completion.str)
      && interface->read_buf.cursor.x > -interface->read_buf.cmd.idx)
  {
    --interface->read_buf.cursor.x;
    while (interface->read_buf.cursor.x > -interface->read_buf.cmd.idx
	   && interface->read_buf.cmd.buf[interface->read_buf.cmd.idx
	   + interface->read_buf.cursor.x]
	   == '\n')
      --interface->read_buf.cursor.x;
  }
  else if (interface->read_buf.completion.str
	   && (interface->read_buf.cursor.x
	       > -interface->read_buf.completion.len))
  {
    --interface->read_buf.cursor.x;
    while (interface->read_buf.cursor.x > -interface->read_buf.completion.len
	   && interface->read_buf.completion.str
	   [interface->read_buf.completion.len + interface->read_buf.cursor.x]
	   == '\n')
      --interface->read_buf.cursor.x;
  }
  launch_completion(interface);
  return (S_SUCCESS);
}

/*
** put the cursor at the start of the cmd line
*/
t_istatus	input_home_response(t_interface *interface)
{
  if (interface->read_buf.completion.str)
    interface->read_buf.cursor.x = -interface->read_buf.completion.len;
  else
    interface->read_buf.cursor.x = -interface->read_buf.cmd.idx;
  return (S_SUCCESS);
}

/*
** put the cursor at the end of the cmd line
*/
t_istatus	input_end_line_response(t_interface *interface)
{
  interface->read_buf.cursor.x = 0;
  return (S_SUCCESS);
}
