/*
** var_tools.c for PSU_2015_42sh in sources/builtins/set
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:53:06 2016 Nicolas Goudal
** Last update Thu Dec 01 15:34:21 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"

void		free_var_list(t_var *list)
{
  t_var		*tmp;

  tmp = list;
  while (list)
  {
    tmp = list->next;
    free(list->value);
    free(list);
    list = tmp;
  }
}

t_status	delete_at_index(t_var_ctrl *scope, int const index)
{
  t_var         *tmp;
  t_var		*delete;

  tmp = scope->list;
  if (tmp && tmp->index == index)
  {
    scope->list = scope->list->next;
    free(tmp->value);
    free(tmp);
  }
  else
  {
    while (tmp->next && tmp->next->index != index)
      tmp = tmp->next;
    if (tmp->next)
    {
      delete = tmp->next;
      tmp->next = delete->next;
      free(delete->value);
      free(delete);
    }
    else
      return (FAILURE);
  }
  return (SUCCESS);
}

static void	find_elem_at_index(t_var_ctrl *scope, t_var *elem)
{
  t_var		*tmp;

  tmp = scope->list;
  while (tmp->next && tmp->next->index < elem->index)
    tmp = tmp->next;
  if (tmp->next && tmp->next->index == elem->index)
  {
    elem->next = tmp->next->next;
    free(tmp->next->value);
    free(tmp->next);
  }
  else
    elem->next = tmp->next;
  tmp->next = elem;
}

void		the_push_at_index(t_var_ctrl *scope, t_var *elem)
{
  if (!scope->list || scope->list->index > elem->index)
  {
    elem->next = scope->list;
    scope->list = elem;
  }
  else if (scope->list->index == elem->index)
  {
    elem->next = scope->list->next;
    free(scope->list->value);
    free(scope->list);
    scope->list = elem;
  }
  else
    find_elem_at_index(scope, elem);
  if (elem->index > scope->nbr)
    scope->nbr = elem->index;
}
