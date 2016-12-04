/*
** functions.c for PSU_2015_42sh in sources/exec/functions
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 01:45:06 2016 Benoit Hamon
** Last update Sun Dec 04 16:58:44 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/builtins.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "shell/exec.h"
#include "builtins/set.h"

extern int		g_signal;

bool			is_function(t_shell *shell, char const *cmd)
{
  t_func_list		*list;

  list = shell->func;
  while (list)
  {
    if (!strcmp(list->name, cmd))
      return (true);
    list = list->next;
  }
  return (false);
}

void			exec_function_simple(t_shell *shell,
					     char const **argv,
					     char const *cmd)
{
  t_return		value;
  int			index;

  value = launch_parser(shell->grammar, cmd, &index);
  if (cmd[index] || !value.ok)
  {
    dprintf(2, "Syntax Error\n");
    shell->carry = false;
  }
  else
  {
    if (shell->stack > MAX_STACK)
    {
      g_signal = true;
      the_puterror(ERR_MSG_INFINITE_LOOP, NULL);
      return ;
    }
    ++shell->stack;
    exec(shell, value.graph);
  }
}

bool			exec_functions(int argc,
				       char const **argv,
				       t_shell *shell)
{
  t_func_list		*list;

  list = shell->func;
  while (list)
  {
    if (!strcmp(list->name, *argv))
    {
      add_tab_var_local(shell, VAR_ARGS, argv + 1);
      exec_function_simple(shell, argv + 1, list->cmd);
      return (shell->carry);
    }
    list = list->next;
  }
  return (false);
}

bool			exec_no_args_functions(char const *name,
					       t_shell *shell)
{
  t_func_list		*list;
  bool			carry;

  list = shell->func;
  shell->stack = 0;
  while (list)
  {
    if (!strcmp(list->name, name))
    {
      carry = shell->carry;
      exec_function_simple(shell, NULL, list->cmd);
      add_int_var_global(shell, VAR_STATUS, !carry);
      shell->carry = carry;
      return (true);
    }
    list = list->next;
  }
  return (false);
}
