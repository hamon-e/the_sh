/*
** cd.c for PSU_2015_42sh in sources/builtins/cd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:45:02 2016 Nicolas Goudal
** Last update Thu Dec 01 15:35:12 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "builtins/set.h"
#include "builtins/set_private.h"
#include "builtins/builtins_msg.h"

static t_status		recreate_tilde_path(char const *path,
					    char const *home_path)
{
  char			*complete_path;

  if (!path[1]
      && chdir(home_path) == -1)
    return (the_putserror(CD_ERR NO_DIRECTORY, home_path));
  else if (path[1] == '/')
  {
    if (!(complete_path
	  = malloc(sizeof(char) * (strlen(home_path) + strlen(path + 1)))))
      return (the_putserror(ERR_MSG_MALLOC, NULL));
    complete_path = strcpy(complete_path, home_path);
    complete_path = strcat(complete_path, path + 1);
    if (chdir(complete_path) == -1)
      return (the_putserror(CD_ERR NO_DIRECTORY, complete_path));
  }
  else
    return (the_putserror(CD_ERR NO_DIRECTORY, path));
  return (SUCCESS);
}

static t_status		cd_tilde(t_shell *shell,
				 char const *path)
{
  int			index;

  if (!!find_env_var(shell->env, "HOME=", &index))
    return (FAILURE);
  if (!path)
  {
    if (chdir(shell->env[index] + 5) == -1)
      return (FAILURE);
  }
  else
    if (!!recreate_tilde_path(path, shell->env[index]))
      return (FAILURE);
  return (SUCCESS);
}

static t_status		cd_dash(char const *oldpwd)
{
  if (!oldpwd)
    return (the_putserror(END_OF_HISTORY, NULL));
  if (chdir(oldpwd) == -1)
    return (the_putserror(CD_ERR NO_DIRECTORY, oldpwd));
  return (SUCCESS);
}

bool			the_cd(int __attribute__((unused))argc,
			       char const *argv[],
			       t_shell *shell)
{
  static char		*oldpwd = NULL;
  char			*pwd;
  char			*tmp;

  tmp = oldpwd;
  if (!(oldpwd = getcwd(NULL, 0)))
    return (false);
  if (!argv[1] || argv[1][0] == '~')
  {
    if (!!cd_tilde(shell, argv[1]))
      return (false);
  }
  else if (argv[1][0] == '-' && !argv[1][1])
  {
    if (!!cd_dash(tmp))
      return (false);
  }
  else if (chdir(argv[1]) == -1 && dprintf(2, CD_ERR NO_DIRECTORY, argv[1]) < 0)
    return (false);
  if (!(pwd = getcwd(NULL, 0))
      || !!add_string_var_export(shell, "PWD", pwd))
    return (false);
  free(tmp);
  free(pwd);
  return (true);
}
