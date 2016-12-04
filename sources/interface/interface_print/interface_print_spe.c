/*
** interface_print_spe.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:30:43 2016 Nicolas Goudal
** Last update Thu Dec 01 11:05:59 2016
*/

#include <stdbool.h>
#include "the_parser/rules.h"
#include "interface/interface_private.h"
#include "interface/interface_print.h"
#include "interface/color.h"

static const t_token_dico	g_token_dico[] =
{
  {PARSER_COMP_STRING, interface_print_comp, ARG_COLOR, 1},
  {PARSER_STRING, interface_print_token, ARG_COLOR, 1},
  {PARSER_INHIBITER, interface_print_token, INHIB_COLOR, 1},
  {PARSER_SUBSTITUTION, interface_print_substitution, -1, 1},
  {PARSER_DOUBLE_QUOTE, interface_print_token, DQUOTE_COLOR, 1},
  {PARSER_SINGLE_QUOTE, interface_print_token, SQUOTE_COLOR, 1},
  {PARSER_VARIABLE, interface_print_token, VAR_COLOR, 0},
  {NULL, NULL, 0, 0}
};

void			interface_print_comp(t_graph *graph,
					     t_interface *interface,
					     char const *color,
					     char const **prev_addr)
{
  int			i;
  char const		*clr;

  while (graph)
  {
    i = 1;
    while (g_token_dico[i].rule)
    {
      if (!the_strcmp(graph->rule, g_token_dico[i].rule))
      {
	if (color)
	  clr = color;
	else
	  clr = interface->color[g_token_dico[i].color].fgd;
	g_token_dico[i].func(graph, interface, clr, prev_addr);
	break ;
      }
      ++i;
    }
    graph = graph->next;
  }
}

void			interface_print_spe(t_graph *graph,
					    t_interface *interface,
					    char const *color,
					    char const **prev_addr)
{
  int			i;
  char const		*clr;

  while (graph)
  {
    i = 0;
    while (g_token_dico[i].rule)
    {
      if (!the_strcmp(graph->rule, g_token_dico[i].rule))
      {
	if (color)
	  clr = color;
	else
	  clr = interface->color[g_token_dico[i].color].fgd;
	if (g_token_dico[i].detail)
	  g_token_dico[i].func(graph->detail, interface, clr, prev_addr);
	else
	  g_token_dico[i].func(graph, interface, clr, prev_addr);
	break ;
      }
      ++i;
    }
    graph = graph->next;
  }
}
