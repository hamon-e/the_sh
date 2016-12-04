/*
** exec_switch.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:50:06 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:43 2016
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

bool		match(char const *s1, char const *s2)
{
  bool		ok;
  int		i;
  int		n;

  n = strlen(s1);
  if (!*s1 && !*s2)
    return (true);
  if (*s2 == '*')
  {
    ok = false;
    i = 0;
    while (!ok && i <= n)
    {
      ok = match(s1 + i, s2 + 1);
      i++;
    }
    return (ok);
  }
  if (*s1 == *s2)
    return (match(s1 + 1, s2 + 1));
  return (false);
}

void		exec_case(t_shell *shell, t_graph *graph, char const *str)
{
  t_arg_list	*arg;
  bool		res;

  if (!graph)
    return ;
  res = false;
  while (graph && !strcmp(PARSER_SPE_STRING, graph->rule))
  {
    if (!(arg = build_spe_string(shell, graph->detail)))
      return ;
    if (match(arg->str, str))
      res = true;
    free(arg->str);
    free(arg);
    graph = graph->next;
  }
  if (res && graph)
    exec(shell, graph);
}

void		exec_switch(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  t_arg_list	*arg;

  tmp = graph->detail;
  if (!tmp || !(arg = build_spe_string(shell, tmp->detail)))
    return ;
  tmp = tmp->next;
  printf("SWITCH %s \n", arg->str);
  while (tmp && !strcmp(PARSER_CASE, tmp->rule))
  {
    exec_case(shell, tmp->detail, arg->str);
    tmp = tmp->next;
  }
  free(arg->str);
  free(arg);
}
