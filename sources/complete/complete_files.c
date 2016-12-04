/*
** complete_files.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:33:44 2016 Nicolas Goudal
** Last update Thu Dec 01 10:53:00 2016
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

t_completion_list		*complete_insert_comp(t_completion_list **list,
						      char const *str,
						      char const *desc)
{
  t_completion_list		*new_comp;

  if ((new_comp = malloc(sizeof(t_completion_list))) == NULL)
    return (NULL);
  new_comp->str = NULL;
  new_comp->desc = NULL;
  new_comp->length = 0;
  new_comp->next = NULL;
  if (str != NULL
      && (new_comp->str = strdup(str)) == NULL)
    return (NULL);
  if (desc != NULL
      && (new_comp->desc = strdup(desc)) == NULL)
    return (NULL);
  new_comp->length = strlen(new_comp->str);
  the_pushback((void **)list, new_comp, offsetof(t_completion_list, next));
  return (*list);
}

static t_status		complete_search_on_folder(char const *file,
						  char const *folder,
						  t_complete_type type,
						  t_completion_list **list)
{
  DIR			*dirp;
  struct dirent		*dp;
  char			*tmp;

  if ((dirp = opendir(folder)) == NULL)
    return (FAILURE);
  while ((dp = readdir(dirp)) != NULL)
  {
    if ((dp->d_name[0] != '.')
	&& ((type == COMPLETE_TYPE_FILES && dp->d_type == DT_REG)
	    || (type == COMPLETE_TYPE_FOLDERS && dp->d_type == DT_DIR)
	    || (type == COMPLETE_TYPE_BOTH)) &&
	!(strncmp(dp->d_name, file, strlen(file))))
    {
      if (!(tmp = malloc(sizeof(char) * (strlen(folder) +
					 strlen(dp->d_name) + 1)))
	  || !(sprintf(tmp, "%s%s", folder, dp->d_name))
	  || !(*list = complete_insert_comp(list, tmp, NULL)))
	return (FAILURE);
      free(tmp);
    }
  }
  if (closedir(dirp) == -1)
    return (FAILURE);
  return (SUCCESS);
}

t_status			complete_search_files(char const *path,
						      t_complete_type type,
						      t_completion_list **list)
{
  char				*file;
  char				*folder;

  if ((folder = complete_get_folder_path(path)) == NULL
      || (file = complete_get_file_path(path)) == NULL
      || complete_search_on_folder(file, folder, type, list) == FAILURE)
    return (FAILURE);
  free(folder);
  free(file);
  return (SUCCESS);
}
