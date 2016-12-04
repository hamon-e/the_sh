/*
** init_shell.c for PSU_2015_42sh in sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Jun 04 20:25:04 2016 Benoit Hamon
** Last update Sun Dec 04 17:11:53 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "opt_parser/opt.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/init_shell.h"
#include "shell/find.h"
#include "shell/exec.h"
#include "complete/complete_private.h"

int			count_name(char const *str, char c)
{
  int			i;

  i = 0;
  while (str[i] && str[i] != c)
    ++i;
  return (i);
}

t_var_ctrl		*cut_env(char const *str)
{
  t_var_ctrl		*var;
  t_var			*elem;
  int			index;
  int			i;
  int			n;

  i = 0;
  index = 1;
  if (!(var = malloc(sizeof(t_var_ctrl))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  *var = (t_var_ctrl){NULL, 0};
  while (str[i])
  {
    if (!(elem = malloc(sizeof(t_var))))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    n = count_name(str + i, ENV_SEPARATOR);
    *elem = (t_var){NULL, index++, NULL};
    if (!(elem->value = strndup(str + i, n)))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    the_pushback((void **)&var->list, elem, offsetof(t_var, next));
    i = str[i + n] ? i + n + 1 : i + n;
  }
  var->nbr = index;
  return (var);
}

bool			build_env(t_shell *shell, char const *envp[])
{
  t_var_list		*var;
  int			n;
  int			i;

  i = 0;
  if (envp && !(shell->env = the_tabdup(envp)))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  while (envp && envp[i])
  {
    if (!(var = malloc(sizeof(t_var_list))))
      return (the_putserror(ERR_MSG_MALLOC, NULL));
    *var = (t_var_list){NULL, NULL, NULL, NULL, NULL};
    if (!(n = count_name(envp[i], ENV_EQUAL))
	|| !(var->name = strndup(envp[i], n))
	|| !(var->export = cut_env(&envp[i][n + 1])))
      return (false);
    the_pushback((void **)&shell->var, var, offsetof(t_var_list, next));
    ++i;
  }
  return (true);
}

static bool		load_functions(t_shell *shell,
				       int opt)
{
  struct dirent		*dir_data;
  DIR			*dir_d;

  if ((opt & OPT_GRAMMAR) != OPT_GRAMMAR)
    return (true);
  if (!(dir_d = opendir(FUNCTIONS_PATH)))
    return (the_putserror(ERR_MSG_OPEN, FUNCTIONS_PATH));
  while ((dir_data = readdir(dir_d)))
    if (*dir_data->d_name != '.')
      exec_file(shell, the_concatchar(FUNCTIONS_PATH,
				      dir_data->d_name,
				      '/'));
  return (true);
}

bool			init_shell(t_shell *shell,
				   char const *envp[],
				   int opt)
{
  *shell = (t_shell){shell->grammar, true, -1, 0, NULL, NULL, NULL, NULL};
  return (build_env(shell, envp)
	  && load_functions(shell, opt)
	  && (shell->complete = complete_init()));
}
