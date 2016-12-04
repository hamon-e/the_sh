/*
** exec_tcsh.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:49:57 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:10 2016
*/

#include <stdbool.h>
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

void		exec_semicolon_tcsh(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;

  tmp = graph->detail;
  while (tmp)
  {
    exec(shell, tmp);
    tmp = tmp->next;
  }
}

void		exec_and_tcsh(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;

  tmp = graph->detail;
  while (tmp)
  {
    exec(shell, tmp);
    if (!shell->carry)
      break ;
    tmp = tmp->next;
  }
}

void		exec_or_tcsh(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;

  tmp = graph->detail;
  while (tmp)
  {
    exec(shell, tmp);
    if (shell->carry)
      break ;
    tmp = tmp->next;
  }
}
