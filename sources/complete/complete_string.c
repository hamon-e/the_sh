/*
** complete_string.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:35:40 2016 Nicolas Goudal
** Last update Thu Dec 01 10:55:44 2016
*/

#include <string.h>
#include <stdio.h>
#include "tools/tools.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

t_status		complete_search_string(char const *command,
					       t_completion_list **list,
					       t_complete_args *flag)
{
  char			**args;
  int			index;

  if (complete_is_flag(command) == 2)
  {
    while (*command && *command != '=')
      command += 1;
    if (*command == '=')
      command += 1;
  }
  if ((args = complete_str_wordtab(flag->string)) == NULL)
    return (FAILURE);
  index = 0;
  while (args[index] != NULL)
  {
    if (!strncmp(args[index], command, strlen(command)))
    {
      if (complete_insert_comp(list, args[index], flag->description) == NULL)
	return (FAILURE);
    }
    index += 1;
  }
  return (SUCCESS);
}
