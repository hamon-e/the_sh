/*
** complete_on_event.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:35:18 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:54 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

static t_status			complete_search_arg(t_complete *complete,
						    t_completion_list **list,
						    t_complete_command *command)
{
  t_complete_args		*flag;

  flag = NULL;
  if (complete_is_flag(command->actual) == 2)
    flag = complete_get_flag(command->actual, complete->args);
  if (flag == NULL)
    flag = complete_get_flag(command->before, complete->args);
  if (flag == NULL || (command->actual && command->actual[0] == '-'))
  {
    if (command->name == NULL)
      return (FAILURE);
    if (command->actual && command->actual[0] == '-'
	&& command->actual[1] == '-')
      complete_long_flag(command->actual, complete, list);
    else if (command->actual && command->actual[0] == '-')
      complete_short_flag(command->actual, complete, list);
    else
      complete_search_files(command->actual, COMPLETE_TYPE_BOTH, list);
  }
  else if (flag->string)
    complete_search_string(command->actual, list, flag);
  else
    complete_search_files(command->actual, flag->type, list);
  return (SUCCESS);
}

t_completion_list		*complete_on_event(t_shell *shell,
						   t_complete_command *command)
{
  t_completion_list		*completion_list;

  if (complete_load(shell, command->name) == FAILURE
      || (completion_list = malloc(sizeof(t_completion_list))) == NULL)
    return (NULL);
  completion_list = NULL;
  complete_search_arg(shell->complete, &completion_list, command);
  return (completion_list);
}
