/*
** complete_flags.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:34:13 2016 Nicolas Goudal
** Last update Thu Dec 01 10:53:38 2016
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools/tools.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

t_status			complete_long_flag(char const *command,
						   t_complete *complete,
						   t_completion_list **list)
{
  t_complete_args		*tmp;

  if (command == NULL)
    return (FAILURE);
  tmp = complete->args;
  while (tmp != NULL)
  {
    if (tmp->long_option
	&& !strncmp(tmp->long_option, command + 2, strlen(command) - 2))
    {
      if (complete_insert_comp(list, tmp->long_option,
			       tmp->description) == NULL)
	return (FAILURE);
    }
    tmp = tmp->next;
  }
  return (SUCCESS);
}

t_status			complete_short_flag(char const *command,
						    t_complete *complete,
						    t_completion_list **list)
{
  t_complete_args		*flag_isset;
  t_complete_args		*tmp;
  char				*new;

  tmp = complete->args;
  if ((flag_isset = complete_get_flag(command, complete->args)) != NULL
      && flag_isset->short_option
      && (strlen(flag_isset->short_option + 1) > 1 || flag_isset->required))
    return (SUCCESS);
  while (tmp != NULL)
  {
    if (tmp->short_option
	&& strlen(tmp->short_option) == 1
	&& strstr(command, tmp->short_option) == NULL)
    {
      if ((new = malloc(sizeof(char) *
			(strlen(command + 1) +
			 strlen(tmp->short_option) + 1))) == NULL
	  || sprintf(new, "%s%s", command + 1, tmp->short_option) < 0
	  || complete_insert_comp(list, new, tmp->description) == NULL)
	return (FAILURE);
    }
    tmp = tmp->next;
  }
  return (SUCCESS);
}
