/*
** access.c for sources in /home/hamon_e/Documents/Tech/Unix/test/parser/sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Apr 07 11:13:22 2016 Benoit Hamon
** Last update Thu Dec 01 15:37:56 2016
*/

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "the_parser/parser.h"
#include "shell/builtins.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "shell/find.h"

int		the_charcmp(char const *str, char const c)
{
  int		i;

  i = 0;
  while (str[i])
  {
    if (str[i] == c)
      return (i);
    ++i;
  }
  return (-1);
}

bool		check_access(char const *str, bool verbose)
{
  if (!!access(str, F_OK))
  {
    if (verbose)
      dprintf(2, "%s: command not found\n", str);
    return (false);
  }
  else if (!!access(str, X_OK))
  {
    if (verbose)
      dprintf(2, "%s: permission denied\n", str);
    return (false);
  }
  return (true);
}

t_cmd_type	the_access(t_shell *shell,
			   t_var *path,
			   char const *cmd,
			   bool verbose)
{
  char		*str;

  if (is_builtin(cmd))
    return (CMD_BUILTIN);
  if (is_function(shell, cmd))
    return (CMD_FUNCTION);
  if (*cmd && the_charcmp(cmd, '/') != -1)
  {
    if (check_access(cmd, verbose))
      return (CMD_DBINARY);
    return (false);
  }
  if (!path || !(str = the_find_path(path, cmd)))
  {
    if (verbose)
      dprintf(2, "%s: command not found\n", cmd);
    return (false);
  }
  free(str);
  return (CMD_PBINARY);
}
