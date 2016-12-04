/*
** interface_print.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:28:52 2016 Nicolas Goudal
** Last update Sun Dec 04 16:57:33 2016 Benoit Hamon
*/

#include <term.h>
#undef tab
#include "tools/tools.h"
#include "interface/interface_private.h"
#include "interface/interface_print.h"

/*
** move back the cursor next to the prompt
*/
void			interface_move_back(t_interface *interface)
{
  t_esc_seq_tab		*esc_seq;

  esc_seq = &interface->esc_seq;
  while (interface->read_buf.len > interface->win_size.ws_col)
  {
    tputs(esc_seq->output[ESOUT_MCURSOR_UP], 0, &the_putchar);
    interface->read_buf.len -= interface->win_size.ws_col;
  }
  tputs(esc_seq->output[ESOUT_CARRIAGE_RETURN], 0, &the_putchar);
  if (interface->read_buf.prompt.x)
    tputs(tparm(esc_seq->output[ESOUT_MCURSOR_RIGHT_X],
		interface->read_buf.prompt.x), 0, &the_putchar);
}

void			interface_print_new_line(t_interface *interface)
{
  int			remove;

  the_putstr(1, "\n");
  if ((remove = (interface->read_buf.len) % (interface->win_size.ws_col)))
    interface->read_buf.len -= remove;
  else
    interface->read_buf.len -=
      ((interface->read_buf.len) % (interface->win_size.ws_col + 1));
  interface->read_buf.len += interface->win_size.ws_col + 1;
}

/*
** get lexer tree
*/
t_graph			*interface_get_tree(t_interface *interface)
{
  t_return		token;
  int			idx;

  idx = 0;
  if (interface->read_buf.completion.str)
  {
    token = launch_parser(interface->lexer,
			  interface->read_buf.completion.str, &idx);
    interface->read_buf.cur_line = interface->read_buf.completion.str;
    interface->read_buf.cur_size = interface->read_buf.completion.len;
  }
  else
  {
    token = launch_parser(interface->lexer,
			  interface->read_buf.cmd.buf, &idx);
    interface->read_buf.cur_line = interface->read_buf.cmd.buf;
    interface->read_buf.cur_size = interface->read_buf.cmd.idx;
  }
  return (token.graph);
}

/*
** move cursor to the start of the current command line
** clear everything below
** print current command line
** move the cursor to the right place
*/
void			interface_print(t_interface *interface,
					t_bool print_cur)
{
  t_graph		*graph;

  tputs(interface->esc_seq.output[ESOUT_CLEAR_BELOW], 1, the_putchar);
  interface->print_cursor = print_cur;
  interface->reserved.is_reserved = B_FALSE;
  interface->reserved.indent = 0;
  interface->read_buf.len = interface->read_buf.prompt.x;
  interface_check_historic(interface);
  if (!(graph = interface_get_tree(interface)))
    interface_print_command_line(interface, NULL);
  else if (graph->detail && !the_strcmp(graph->detail->rule, "lexer"))
    interface_print_command_line(interface, graph->detail->detail);
  interface_print_completion(interface);
  if (print_cur)
    interface_move_back(interface);
  else
    interface->read_buf.len = 0;
  the_free(1, FREE_GRAPH, graph);
}
