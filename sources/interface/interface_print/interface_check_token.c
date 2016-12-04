/*
** interface_check_token.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:28:27 2016 Nicolas Goudal
** Last update Thu Dec 01 11:03:01 2016
*/

#include <term.h>
#include <unistd.h>
#include "interface/interface_print.h"
#include "interface/interface_private.h"
#include "the_parser/rules.h"

static const t_token_dico	g_token_dico[] =
{
  {PARSER_CMD, interface_print_cmd, -1, 1},
  {PARSER_RESERVED, interface_print_reserved, RESERVED_COLOR, 0},
  {PARSER_RESERVED_NO, interface_print_reserved_no, RESERVED_COLOR, 0},
  {PARSER_RESERVED_END, interface_print_reserved_end, RESERVED_COLOR, 0},
  {PARSER_REDIR, interface_print_token, DEFAULT_COLOR, 1},
  {PARSER_COMBINERS, interface_print_combiner, COMBINER_COLOR, 0},
  {NULL, 0, -1, 0},
};

void			interface_print_check_token(t_graph *graph,
						    t_interface *interface,
						    char const **prev_addr)
{
  int			i;
  char const		*color;

  i = 0;
  if (!graph)
    return ;
  while (g_token_dico[i].rule)
  {
    if (!the_strcmp(g_token_dico[i].rule, graph->rule))
    {
      if (g_token_dico[i].color >= 0)
	color = interface->color[g_token_dico[i].color].fgd;
      else
	color = NULL;
      if (g_token_dico[i].detail)
	g_token_dico[i].func(graph->detail, interface, color, prev_addr);
      else
	g_token_dico[i].func(graph, interface, color, prev_addr);
    }
    ++i;
  }
}

static void	interface_end_command(t_interface *interface)
{
  if (interface->print_cursor
      && interface->read_buf.completion.type == LINE_COMPL)
  {
    tputs(interface->color[COMPL_COLOR].fgd, 0, &the_putchar);
    tputs(interface->esc_seq.output[ESOUT_ENTER_STANDOUT], 1, the_putchar);
    interface_print_str(interface->read_buf.completion.aff,
			1, interface);
    tputs(interface->esc_seq.output[ESOUT_EXIT_STANDOUT], 1, the_putchar);
    interface_print_str(interface->read_buf.completion.aff + 1,
			interface->read_buf.completion.aff_len - 1, interface);
    tputs(interface->color[DEFAULT_COLOR].fgd, 0, &the_putchar);
  }
  else if (!interface->read_buf.cursor.x && interface->print_cursor)
  {
    ++interface->read_buf.len;
    tputs(interface->esc_seq.output[ESOUT_ENTER_STANDOUT], 1, the_putchar);
    write(1, " ", 1);
    tputs(interface->esc_seq.output[ESOUT_EXIT_STANDOUT], 1, the_putchar);
  }
}

void		interface_print_command_line(t_interface *interface,
					     t_graph *graph)
{
  char const	*prev_addr;

  if (!interface->read_buf.completion.str)
    prev_addr = interface->read_buf.cmd.buf;
  else
    prev_addr = interface->read_buf.completion.str;
  while (graph)
  {
    interface_print_check_token(graph, interface, &prev_addr);
    graph = graph->next;
  }
  if (prev_addr < interface->read_buf.cur_line + interface->read_buf.cur_size)
  {
    tputs(interface->color[UNKNOWN_COLOR].fgd, 1, &the_putchar);
    interface_print_str(prev_addr, interface->read_buf.cur_line
			+ interface->read_buf.cur_size - prev_addr, interface);
    tputs(interface->color[DEFAULT_COLOR].fgd, 1, &the_putchar);
  }
  interface_end_command(interface);
}
