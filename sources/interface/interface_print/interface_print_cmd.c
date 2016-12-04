/*
** interface_print_cmd.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:29:20 2016 Nicolas Goudal
** Last update Thu Dec 01 15:39:38 2016
*/

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/find.h"
#include "interface/interface_print.h"
#include "interface/interface_private.h"
#include "interface/color.h"

static const t_token_dico	g_token_dico[] =
{
  {PARSER_SPE_STRING, interface_print_spe, -1, 1},
  {PARSER_COMP_STRING, interface_print_comp, -1, 1},
  {PARSER_SUBSTITUTION, interface_print_substitution, -1, 1},
  {PARSER_REDIR, interface_print_redir, DEFAULT_COLOR, 1},
  {NULL, NULL, 0, 0}
};

static void	interface_print_command(t_graph *graph,
					t_interface *interface,
					char const **prev_addr)
{
  char		*str;
  t_var		*var;
  char const	*color;

  color = interface->color[CMD_COLOR].fgd;
  if ((str = strndup(graph->str, graph->size))
      && (var = the_find_env(interface->shell->var, VAR_PATH))
      && !(the_access(interface->shell, var, str, false)))
    color = interface->color[UNKNOWN_COLOR].fgd;
  interface_print_token(graph, interface,
			color, prev_addr);
}

void		interface_print_cmd(t_graph *graph,
				    t_interface *interface,
				    char *color __attribute__((unused)),
				    char const **prev_addr)
{
  int		i;
  char		*clr;

  if (!graph)
    return ;
  interface_print_command(graph, interface, prev_addr);
  graph = graph->next;
  while (graph && graph->rule)
  {
    i = 0;
    while (g_token_dico[i].rule)
    {
      if (!the_strcmp(graph->rule, g_token_dico[i].rule))
      {
	if (g_token_dico[i].color >= 0)
	  clr = interface->color[g_token_dico[i].color].fgd;
	else
	  clr = NULL;
	g_token_dico[i].func(graph->detail, interface, clr, prev_addr);
      }
      ++i;
    }
    graph = graph->next;
  }
}
