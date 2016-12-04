/*
** build_redir.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:31:57 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:32 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static const t_redir_func	g_redir_dico[] =
{
  {PARSER_REDIR_LEFT, REDIR_LEFT},
  {PARSER_REDIR_RIGHT, REDIR_RIGHT},
  {PARSER_REDIR_DOUBLE_LEFT, REDIR_DOUBLE_LEFT},
  {PARSER_REDIR_DOUBLE_RIGHT, REDIR_DOUBLE_RIGHT},
  {NULL, 0}
};

static t_redir_list	*build_redir_type(t_shell *shell,
					  t_graph *graph,
					  t_redir_list *list)
{
  t_arg_list		*name;
  int			i;

  while (graph)
  {
    if (!strcmp(PARSER_FD, graph->rule))
      list->fd = *graph->str - '0';
    else if (!strcmp(PARSER_COMP_STRING, graph->rule))
    {
      if (!(name = build_comp_string(shell, graph->detail)))
	return (the_puterror(ERR_MSG_MALLOC, NULL));
      list->name = name->str;
    }
    else
    {
      i = 0;
      while (g_redir_dico[i].rule && strcmp(g_redir_dico[i].rule, graph->rule))
	++i;
      if (g_redir_dico[i].rule)
	list->type = g_redir_dico[i].type;
    }
    graph = graph->next;
  }
  return (list->type && list->name ? list : the_free(1, FREE_REDIR, list));
}

t_redir_list		*build_redir(t_shell *shell, t_graph *graph)
{
  t_redir_list		*list;
  void			*data;

  if (!graph)
    return (NULL);
  if (!(list = malloc(sizeof(t_redir_list))))
  {
    the_puterror(ERR_MSG_MALLOC, NULL);
    return (NULL);
  }
  *list = (t_redir_list){0, -1, NULL, NULL};
  if (!(data = build_redir_type(shell, graph, list)))
    return (NULL);
  return (list);
}
