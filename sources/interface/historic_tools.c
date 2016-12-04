/*
** historic_tools.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:20:24 2016 Nicolas Goudal
** Last update Thu Dec 01 10:57:31 2016
*/

#include <stdlib.h>
#include <string.h>
#include "interface/interface_private.h"
#include "interface/historic_private.h"

t_historic_dir_list	*historic_new_dir(t_historic_dir_list **list,
					  char *name)
{
  t_historic_dir_list	*dir;

  if (!(dir = malloc(sizeof(t_historic_dir_list))))
  {
    free(name);
    return (NULL);
  }
  dir->name = name;
  dir->cmd = NULL;
  dir->next = NULL;
  the_pushback((void **)list, dir, offsetof(t_historic_dir_list, next));
  return (dir);
}

t_historic_dir_list	*historic_get_dir(t_historic_dir_list **list,
					  char *name)
{
  t_historic_dir_list	*tmp;

  tmp = *list;
  while (tmp)
  {
    if (!(the_strcmp(name, tmp->name)))
      return (tmp);
    tmp = tmp->next;
  }
  return (historic_new_dir(list, strdup(name)));
}

t_istatus		historic_new_cmd(t_historic_dir_list *dir,
					 char *str)
{
  t_historic_cmd_list	*cmd;

  cmd = NULL;
  if (!str || !(*str) || !(dir)
      || (dir->cmd && !the_strcmp(dir->cmd->str, str))
      || !(cmd = malloc(sizeof(t_historic_cmd_list))))
  {
    free(str);
    free(cmd);
    return (S_FAILURE);
  }
  cmd->str = str;
  cmd->next = NULL;
  cmd->prev = NULL;
  the_pushfront2((void **)&dir->cmd, cmd,
		 offsetof(t_historic_cmd_list, next),
		 offsetof(t_historic_cmd_list, prev));
  return (S_SUCCESS);
}
