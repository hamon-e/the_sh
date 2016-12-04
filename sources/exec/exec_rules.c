/*
** exec_rules.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:37:03 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:04 2016
*/

#include <stdbool.h>
#include <string.h>
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

void		exec_or(t_shell *shell, t_graph *graph)
{
  if (!shell->carry)
    exec(shell, graph);
}

void		exec_and(t_shell *shell, t_graph *graph)
{
  if (shell->carry)
    exec(shell, graph);
}

void		exec_not(t_shell *shell, t_graph *graph)
{
  exec(shell, graph);
  shell->carry = !shell->carry;
}

void		exec_bgnd(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;

  tmp = graph->detail;
  while (tmp)
  {
    exec(shell, tmp);
    tmp = tmp->next;
  }
}

static const t_rule_func	g_rule_combiners_dico[] =
{
  {PARSER_OR, exec_or},
  {PARSER_AND, exec_and},
  {PARSER_NOT, exec_not},
  {NULL, NULL},
};

void		exec_combiners(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  int		i;

  i = 0;
  tmp = graph->detail;
  if (!tmp)
    return ;
  while (g_rule_combiners_dico[i].f
	 && strcmp(g_rule_combiners_dico[i].rule, tmp->rule))
    ++i;
  if (tmp->next && g_rule_combiners_dico[i].f)
    g_rule_combiners_dico[i].f(shell, tmp->next);
  else
    exec(shell, tmp);
}
