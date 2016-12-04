/*
** exec_if.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:02:28 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:33 2016
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

bool		exec_condition(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  bool		res;

  tmp = graph;
  if (!tmp)
    return (true);
  exec(shell, tmp);
  res = shell->carry;
  if (!(tmp = tmp->next)
      || strcmp(PARSER_ENTRY, tmp->rule))
    return (res);
  if (res)
    exec(shell, tmp);
  return (res);
}

void		exec_if(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  int		res;

  tmp = graph->detail;
  res = false;
  while (!res && tmp && !strcmp(PARSER_CONDITION, tmp->rule))
  {
    res = exec_condition(shell, tmp->detail);
    tmp = tmp->next;
  }
  if (!res && tmp && !strcmp(PARSER_ELSE, tmp->rule))
    exec(shell, tmp->detail);
}
