/*
** build_index.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:31:48 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:44 2016
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static t_index_list	*build_index_nbr(t_graph *graph)
{
  t_index_list		*elem;

  if (!(elem = malloc(sizeof(t_index_list))))
    return (NULL);
  elem->index = the_atoi(graph->str);
  elem->next = NULL;
  return (elem);
}

static void		get_max(int *n1, int *n2)
{
  int			tmp;

  if (*n1 > *n2)
  {
    tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
  }
}

static t_index_list	*build_index_range(t_graph *graph)
{
  t_index_list		*list;
  t_index_list		*elem;
  int			n1;
  int			n2;

  list = NULL;
  if (!graph || !graph->next)
    return (NULL);
  n1 = the_atoi(graph->str);
  n2 = the_atoi(graph->next->str);
  get_max(&n1, &n2);
  while (n1 <= n2)
  {
    if (!(elem = malloc(sizeof(t_index_list))))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    *elem = (t_index_list){n1, NULL};
    the_pushback((void **)&list, elem, offsetof(t_index_list, next));
    ++n1;
  }
  return (list);
}

bool			keep_index(t_index_list *list, int max, int index)
{
  if (!list)
    return (true);
  while (list)
  {
    if (index == list->index
	|| (list->index < 0 && list->index + max == index))
      return (true);
    list = list->next;
  }
  return (false);
}

t_index_list		*build_index(t_graph *graph)
{
  t_index_list		*list;
  t_index_list		*elem;

  list = NULL;
  while (graph)
  {
    elem = NULL;
    if (!strcmp(PARSER_RANGE, graph->rule))
      elem = build_index_range(graph->detail);
    if (!strcmp(PARSER_NUMBER, graph->rule))
      elem = build_index_nbr(graph);
    if (!elem)
      return (NULL);
    the_pushback((void **)&list, elem, offsetof(t_index_list, next));
    graph = graph->next;
  }
  return (list);
}
