/*
** interface_print_redir.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:29:59 2016 Nicolas Goudal
** Last update Thu Dec 01 11:05:36 2016
*/

#include <stdbool.h>
#include "the_parser/rules.h"
#include "interface/interface_private.h"
#include "interface/interface_print.h"
#include "interface/color.h"

void		interface_print_substitution(t_graph *graph,
					     t_interface *interface,
					     char const *color,
					     char const **prev_addr)
{
  (void)color;
  interface_print_token(graph, interface,
			interface->color[INHIB_COLOR].fgd, prev_addr);
  if (graph && (graph = graph->next))
    interface_print_check_token(graph->detail, interface, prev_addr);
  if (graph && (graph = graph->next))
    interface_print_token(graph, interface,
			  interface->color[INHIB_COLOR].fgd, prev_addr);
}

void		interface_print_redir(t_graph *graph,
				      t_interface *interface,
				      char const *color,
				      char const **prev_addr)
{
  while (graph)
  {
    interface_print_token(graph, interface, color, prev_addr);
    graph = graph->next;
  }
}
