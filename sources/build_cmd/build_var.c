/*
** build_var.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:32:30 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:37 2016
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static t_var_ctrl	*get_var_scope(t_var_list *var, char const *name)
{
  while (var)
  {
    if (!strcmp(var->name, name))
    {
      if (var->local)
	return (var->local);
      if (var->global)
	return (var->global);
      if (var->export)
	return (var->export);
      return (NULL);
    }
    var = var->next;
  }
  return (NULL);
}

static t_arg_list	*get_var(t_var_list *var_list,
				 char const *name,
				 t_index_list *index)
{
  t_arg_list		*arg_list;
  t_arg_list		*elem;
  t_var_ctrl		*var;
  t_var			*tmp;

  if (!(var = get_var_scope(var_list, name)))
    return (the_puterror(ERR_MSG_VARIABLE, name));
  arg_list = NULL;
  tmp = var->list;
  while (tmp)
  {
    if (keep_index(index, var->nbr, tmp->index))
    {
      if (!(elem = malloc(sizeof(t_cmd_list)))
	  || !(elem->str = strdup(tmp->value)))
	return (the_puterror(ERR_MSG_MALLOC, NULL));
      elem->next = NULL;
      the_pushback((void**)&arg_list, elem, offsetof(t_arg_list, next));
    }
    tmp = tmp->next;
  }
  return (arg_list);
}

t_arg_list		*build_var(t_shell *shell, t_graph *graph)
{
  t_arg_list		*list;
  char const		*name;
  t_index_list		*index;

  if (!graph)
    return (NULL);
  index = NULL;
  list = NULL;
  if (!(name = strndup(graph->str, graph->size)))
  {
    the_puterror(ERR_MSG_MALLOC, NULL);
    return (NULL);
  }
  if (graph->next)
    index = build_index(graph->next->detail);
  list = get_var(shell->var, name, index);
  the_free(2, FREE_STR, name, FREE_LST_INDEX, index);
  return (list);
}
