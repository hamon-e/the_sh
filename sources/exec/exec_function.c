/*
** exec_function.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:49:01 2016 Nicolas Goudal
** Last update Thu Dec 01 15:35:59 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

void		delete_function(t_func_list **func, char const *name)
{
  t_func_list	*list;
  t_func_list	*tmp;

  list = *func;
  if (!list)
    return ;
  if (!strcmp(list->name, name))
  {
    the_free(1, FREE_FUNC, list);
    *func = NULL;
  }
  while (list && list->next)
  {
    if (!strcmp(list->next->name, name))
    {
      tmp = list->next->next;
      the_free(1, FREE_FUNC, list->next);
      list->next = tmp;
    }
    list = list->next;
  }
}

void		exec_function(t_shell *shell, t_graph *graph)
{
  t_graph	*tmp;
  t_func_list	*list;
  t_arg_list	*arg;

  tmp = graph->detail;
  if (!tmp || !tmp->next)
    return ;
  if (!(list = malloc(sizeof(t_func_list)))
      || !(arg = build_comp_string(shell, tmp->detail))
      || !(list->cmd = strndup(tmp->next->str, tmp->next->size)))
  {
    the_puterror(ERR_MSG_MALLOC, NULL);
    return ;
  }
  list->name = arg->str;
  list->next = NULL;
  free(arg);
  delete_function(&shell->func, list->name);
  the_pushback((void **)&shell->func, list, offsetof(t_func_list, next));
}
