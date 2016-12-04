/*
** build_comp_string.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:31:28 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:27 2016
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

t_arg_list		*build_comp_string(t_shell *shell, t_graph *graph)
{
  t_arg_list		*(*f)();
  t_arg_list		*list;
  t_arg_list		*elem;
  t_arg_list		*arg_list;

  list = NULL;
  if (!(arg_list = malloc(sizeof(t_arg_list))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  while (graph && (f = is_comp_string(graph->rule)))
  {
    if (!(elem = f(shell, graph)))
      return (NULL);
    the_pushback((void **)&list, elem, offsetof(t_arg_list, next));
    graph = graph->next;
  }
  if (!(arg_list->str = the_list_to_str(list,
					offsetof(t_arg_list, str),
					offsetof(t_arg_list, next))))
    return (NULL);
  arg_list->next = NULL;
  return (arg_list);
}
