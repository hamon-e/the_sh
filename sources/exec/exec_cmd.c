/*
** exec_cmd.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:47:18 2016 Nicolas Goudal
** Last update Thu Dec 01 15:37:02 2016
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/builtins.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"
#include "builtins/set.h"

void		print_cmd(t_cmd *cmd)
{
  int		i;

  for (i = 0; cmd->tab[i]; ++i)
    printf("%s\n", cmd->tab[i]);
  while (cmd->redir_list)
  {
    printf("%s %d\n", cmd->redir_list->name, cmd->redir_list->fd);
    cmd->redir_list = cmd->redir_list->next;
  }
  printf("\n");
}

bool		exec_dbinary(int argc, char const **argv, t_shell *shell)
{
  bool		res;
  int		status;
  int		pid;

  if ((pid = fork()) < 0)
    return (false);
  if (!pid)
  {
    execve(*argv, (char *const *)argv, (char *const *)shell->env);
    dprintf(2, "Permission denied\n");
    exit(1);
  }
  wait(&status);
  res = false;
  if (WIFSIGNALED(status))
  {
    print_signal(*argv, WTERMSIG(status));
    add_int_var_global(shell, VAR_STATUS, WTERMSIG(status) + 127);
  }
  else if (WIFEXITED(status))
  {
    add_int_var_global(shell, VAR_STATUS, WEXITSTATUS(status));
    res = WEXITSTATUS(status) == 0;
  }
  return (res);
}

bool		exec_pbinary(int argc, char const **argv, t_shell *shell)
{
  char const	*cmd;
  t_var		*path;

  path = the_find_env(shell->var, "PATH");
  if (!(cmd = the_find_path(path, *argv)))
    return (false);
  free((void *)*argv);
  *argv = cmd;
  return (exec_dbinary(argc, argv, shell));
}

static const t_exec_func	g_exec_dico[] =
{
  {CMD_DBINARY, exec_dbinary},
  {CMD_PBINARY, exec_pbinary},
  {CMD_BUILTIN, exec_builtin},
  {CMD_FUNCTION, exec_functions}
};

void		exec_cmd_second(t_shell *shell, t_cmd *cmd, t_cmd_type type)
{
  int		fd_save[3];
  bool		res;
  int		i;

  if (cmd->redir_list && !exec_redir(cmd->redir_list, fd_save))
  {
    shell->carry = false;
    return ;
  }
  i = 0;
  while (g_exec_dico[i].type != type)
    ++i;
  res = g_exec_dico[i].f(the_tablen(cmd->tab), cmd->tab, shell);
  if (cmd->redir_list && !exec_reset_fd(fd_save))
  {
    shell->carry = false;
    return ;
  }
  if (type == CMD_BUILTIN || type == CMD_FUNCTION)
    add_int_var_global(shell, VAR_STATUS, !res);
  shell->carry = res;
}

void		exec_cmd(t_shell *shell, t_graph *graph)
{
  t_cmd_type	type;
  t_cmd		*cmd;
  t_var		*path;

  cmd = build_cmd(shell, graph->detail);
  path = the_find_env(shell->var, "PATH");
  if (!cmd || !cmd->tab)
  {
    the_puterror(ERR_MSG_CMD, NULL);
    shell->carry = false;
    return ;
  }
  if (!(type = the_access(shell, path, *cmd->tab, true)))
  {
    add_int_var_global(shell, VAR_STATUS, 1);
    shell->carry = false;
    return ;
  }
  exec_cmd_second(shell, cmd, type);
}
