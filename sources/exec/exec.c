/*
** exec.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:48:10 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:28 2016
*/

#include <stdbool.h>
#include <string.h>
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

static const t_rule_func	g_rule_dico[] =
{
  {PARSER_SEMICOLON_TCSH, exec_semicolon_tcsh},
  {PARSER_OR_TCSH, exec_or_tcsh},
  {PARSER_AND_TCSH, exec_and_tcsh},
  {PARSER_COMBINERS, exec_combiners},
  {PARSER_PIPE, exec_pipe},
  {PARSER_BGND, exec_bgnd},
  {PARSER_IF, exec_if},
  {PARSER_SWITCH, exec_switch},
  {PARSER_FUNCTION, exec_function},
  {PARSER_CMD, exec_cmd},
  {PARSER_WHILE, exec_while},
  {NULL, NULL},
};

void		exec(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  int		i;

  i = 0;
  if (!graph)
    return ;
  while (g_rule_dico[i].rule && strcmp(g_rule_dico[i].rule, graph->rule))
    ++i;
  if (g_rule_dico[i].rule)
    g_rule_dico[i].f(shell, graph);
  else
  {
    tmp = graph->detail;
    while (tmp)
    {
      exec(shell, tmp);
      tmp = tmp->next;
    }
  }
}
