/*
** exec_pipe.c for PSU_2015_42sh in sources/exec
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Jun 04 14:51:33 2016 Benoit Hamon
** Last update Sun Dec 04 17:11:02 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

static void	the_pipe_child(int *fildes,
			       t_shell *shell,
			       t_graph *graph)
{
  if (close(fildes[1]) == -1
      || dup2(fildes[0], 0) == -1)
    shell->carry = 0;
  else if (graph->next && graph->next->next)
    the_pipe(shell, graph->next);
  else
    exec(shell, graph->next);
  exit(1);
}

static int	the_pipe_father(int *fildes,
				t_shell *shell,
				t_graph *graph)
{
  int		pid;
  int		status;

  if ((pid = fork()) == -1)
    return (FAILURE);
  else if (!pid)
  {
    if (dup2(fildes[1], 1) != -1)
      exec(shell, graph);
    exit(1);
  }
  else
  {
    if (waitpid(pid, &status, 0) == -1
	|| close(fildes[1]) == -1)
      return (FAILURE);
    return (SUCCESS);
  }
}

void		the_pipe(t_shell *shell, t_graph *graph)
{
  int		pid;
  int		fildes[2];
  int		status;

  if (pipe(fildes)
      || (pid = fork()) == -1)
    shell->carry = 0;
  else if (!pid)
    the_pipe_child(fildes, shell, graph);
  else
  {
    if (close(fildes[0]) == -1)
      shell->carry = 0;
    else
    {
      the_pipe_father(fildes, shell, graph);
      if (waitpid(pid, &status, 0) == -1)
	shell->carry = 0;
    }
  }
}

void		exec_pipe(t_shell *shell, t_graph *graph)
{
  if (!graph->detail)
    shell->carry = false;
  else if (!graph->detail->next)
    exec(shell, graph->detail);
  else
    the_pipe(shell, graph->detail);
}
