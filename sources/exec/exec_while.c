/*
** exec_while.c for PSU_2015_42sh in sources/exec
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Jun 05 19:23:40 2016 Benoit Hamon
** Last update Thu Dec 01 15:35:53 2016
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

extern int	g_signal;

void		exec_while(t_shell *shell, t_graph *graph)
{
  t_graph	*condition;
  t_graph	*tmp;

  if (!graph->detail)
    return ;
  g_signal = false;
  condition = graph->detail;
  tmp = graph->detail->next;
  while (!g_signal)
  {
    exec(shell, condition->detail);
    if (shell->carry && tmp)
      exec(shell, tmp->detail);
    else if (!shell->carry)
      break ;
  }
  g_signal = false;
}
