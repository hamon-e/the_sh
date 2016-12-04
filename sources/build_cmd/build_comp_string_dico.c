/*
** build_comp_string_dico.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:31:34 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:20 2016
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static t_arg_list	*build_string(t_shell
				      __attribute__((unused))*shell,
				      t_graph *graph)
{
  t_arg_list		*list;

  if (!(list = malloc(sizeof(t_arg_list)))
      || !(list->str = strndup(graph->str, graph->size)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  list->next = NULL;
  return (list);
}

static t_arg_list	*build_inhibiter(t_shell
					 __attribute__((unused))*shell,
					 t_graph *graph)
{
  t_arg_list		*list;
  int			i;

  if (!(list = malloc(sizeof(t_arg_list)))
      || !(list->str = malloc(sizeof(char) * 2)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  list->next = NULL;
  i = 0;
  while (ESCAPE_SEQUENCE[i] && ESCAPE_SEQUENCE[i] != graph->str[1])
    ++i;
  list->str[0] = ESCAPE_SEQUENCE[i] ? '\a' + i : graph->str[1];
  list->str[1] = '\0';
  return (list);
}

static t_arg_list	*build_single_quote(t_shell
					    __attribute__((unused))*shell,
					    t_graph *graph)
{
  t_arg_list		*list;
  int			i;
  int			j;
  int			k;

  if (!(list = malloc(sizeof(t_arg_list)))
      || !(list->str = malloc(sizeof(char) * (graph->size - 2 + 1))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  list->next = NULL;
  i = 0;
  j = 1;
  k = 0;
  while (i < graph->size - 2 - k)
  {
    if (graph->str[j] == '\\' && graph->str[j + 1] == '\'')
    {
      ++j;
      ++k;
    }
    list->str[i++] = graph->str[j++];
  }
  list->str[i] = '\0';
  return (list);
}

static t_arg_list	*build_double_quote(t_shell
					    __attribute__((unused))*shell,
					    t_graph *graph)
{
  t_arg_list		*list;

  if (!(list = malloc(sizeof(t_arg_list)))
      || !(list->str = strndup(graph->str + 1, graph->size - 2)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  list->next = NULL;
  return (list);
}

static const t_arg_func	g_comp_string_dico[] =
{
  {PARSER_STRING, build_string},
  {PARSER_INHIBITER, build_inhibiter},
  {PARSER_SINGLE_QUOTE, build_single_quote},
  {PARSER_DOUBLE_QUOTE, build_double_quote},
  {NULL, NULL}
};

t_arg_list		*(*is_comp_string(char const *str))()
{
  int			i;

  i = 0;
  while (g_comp_string_dico[i].f && strcmp(g_comp_string_dico[i].rule, str))
    ++i;
  return (g_comp_string_dico[i].f);
}
