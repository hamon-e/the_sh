/*
** complete_tools.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:35:51 2016 Nicolas Goudal
** Last update Thu Dec 01 10:55:58 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "complete/complete.h"

char			*complete_get_folder_path(char const *path)
{
  char			*folder;
  int			index;

  if (path == NULL)
    return (strdup("./"));
  index = strlen(path);
  while (index >= 0 && path[index] != '/')
    index -= 1;
  if (index < 0)
    return (strdup("./"));
  if ((folder = malloc(sizeof(char) * (index + 2))) == NULL ||
      (snprintf(folder, index + 2, "%s", path)) == -1)
    return (NULL);
  return (folder);
}

char			*complete_get_file_path(char const *path)
{
  char			*file;
  int			index;
  int			count;

  if (path == NULL)
    return (strdup(""));
  count = strlen(path);
  while (count - 1 >= 0 && path[count - 1] != '/')
    count -= 1;
  if ((file = malloc(sizeof(char) * (strlen(path) - count + 1))) == NULL)
    return (NULL);
  index = 0;
  while (path != NULL && path[count + index])
  {
    file[index] = path[count + index];
    index += 1;
  }
  file[index] = '\0';
  return (file);
}

int				complete_is_flag(char const *str)
{
  if (str == NULL)
    return (0);
  if (str[0] == '-' && str[1] == '-' && str[2])
    return (2);
  else if (str[0] == '-' && str[1])
    return (1);
  return (0);
}

t_complete_args			*complete_get_flag(char const *flag,
						   t_complete_args *args)
{
  t_complete_args		*tmp;
  bool				short_option;
  int				cmd_len;
  int				len;

  if (args == NULL || flag == NULL || complete_is_flag(flag) == 0)
    return (NULL);
  short_option = (complete_is_flag(flag) == 1) ? true : false;
  tmp = args;
  cmd_len = strlen(flag) - 2;
  while (tmp != NULL)
  {
    if (short_option == false && tmp->long_option != NULL)
    {
      len = strlen(tmp->long_option);
      len = (cmd_len > len) ? len : cmd_len;
      if (!(strncmp(tmp->long_option, flag + 2, len)))
	return (tmp);
    }
    else if (short_option == true && tmp->short_option
	     && !(strcmp(tmp->short_option, flag + 1)))
      return (tmp);
    tmp = tmp->next;
  }
  return (NULL);
}
