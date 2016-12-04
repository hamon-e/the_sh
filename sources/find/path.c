/*
** path.c for sources in /home/hamon_e/Documents/Tech/Unix/test/parser/sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Apr 07 11:34:27 2016 Benoit Hamon
** Last update Thu Dec 01 15:37:51 2016
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/find.h"

t_var		*the_find_env(t_var_list *var, char const *name)
{
  while (var)
  {
    if (!strcmp(var->name, name))
      return (var->export->list);
    var = var->next;
  }
  return (NULL);
}

char		*the_concatchar(char const *dir, char const *file, char c)
{
  char		*res;
  int		i;
  int		j;

  if (!(res = malloc(sizeof(char) * (strlen(dir) + strlen(file) + 2))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  i = 0;
  while (dir && dir[i])
  {
    res[i] = dir[i];
    ++i;
  }
  j = 0;
  if (i && res[i - 1] != c)
    res[i++] = c;
  while (file && file[j])
    res[i++] = file[j++];
  res[i] = 0;
  return (res);
}

char		*the_find_path(t_var *path, char const *cmd)
{
  char		*tmp;

  while (path)
  {
    if (!(tmp = the_concatchar(path->value, cmd, '/')))
      return (NULL);
    if (check_access(tmp, false) == true)
      break ;
    free(tmp);
    tmp = NULL;
    path = path->next;
  }
  return (tmp);
}
