/*
** complete_load.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:34:30 2016 Nicolas Goudal
** Last update Thu Dec 01 20:17:28 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/exec.h"
#include "complete/complete.h"
#include "complete/complete_private.h"
#include "interface/interface_complete.h"

t_complete			*complete_init()
{
  t_complete			*complete;

  if ((complete = malloc(sizeof(t_complete))) == NULL)
    return (NULL);
  complete->name = NULL;
  complete->args = NULL;
  return (complete);
}

static t_status			complete_fill(char const *command_name,
					      t_shell *shell)
{
  char				*name;
  char				*path;
  DIR				*dirp;
  struct dirent			*dp;

  if ((name = malloc(sizeof(char) * (strlen(command_name) +
				     strlen(COMPLETE_EXT) + 1))) == NULL
      || (sprintf(name, "%s%s", command_name, COMPLETE_EXT)) <= 0
      || (dirp = opendir(DIR_COMPLETE)) == NULL)
    return (FAILURE);
  while ((dp = readdir(dirp)) != NULL)
  {
    if (!(strcmp(dp->d_name, name)))
    {
      if ((path = malloc(sizeof(char) * (strlen(DIR_COMPLETE) +
					 strlen(name) + 2))) == NULL
	  || (sprintf(path, "%s/%s", DIR_COMPLETE, name)) <= 0)
	return (FAILURE);
      exec_file(shell, path);
      free(path);
      break ;
    }
  }
  free(name);
  return ((closedir(dirp) == -1) ? FAILURE : SUCCESS);
}

static void			free_args(t_complete_args *list)
{
  t_complete_args		*tmp;

  if (list != NULL)
  {
    tmp = list;
    free_args(list->next);
    free(tmp);
  }
}

t_status			complete_load(t_shell *shell,
					      char const *command_name)
{
  if (command_name == NULL)
    return (FAILURE);
  if (shell->complete->name == NULL
      || !!(strcmp(command_name, shell->complete->name)))
  {
    free_args(shell->complete->args);
    shell->complete->args = NULL;
    if (shell->complete->name)
      free(shell->complete->name);
    if ((shell->complete->name = strdup(command_name)) == NULL
	|| complete_fill(shell->complete->name, shell) == FAILURE)
      return (FAILURE);
  }
  return (SUCCESS);
}
