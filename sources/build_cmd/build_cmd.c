/*
** build_cmd.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:31:24 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:07 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <glob.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static const t_arg_func	g_spe_str_dico[] =
{
  {PARSER_VARIABLE, build_var},
  {PARSER_SUBSTITUTION, build_substitution},
  {PARSER_COMP_STRING, build_comp_string},
  {NULL, NULL}
};

static const char	**build_glob(t_arg_list *cmd)
{
  glob_t		glob_s;
  char const		**tab;
  int			flags;

  flags = GLOB_TILDE | GLOB_NOCHECK | GLOB_BRACE;
  glob_s.gl_pathv = NULL;
  while (cmd)
  {
    if (glob(cmd->str, flags, NULL, &glob_s) != 0)
    {
      globfree(&glob_s);
      return (NULL);
    }
    flags |= GLOB_APPEND;
    cmd = cmd->next;
  }
  if (!(tab = (char const **)the_tabdup((char const **)glob_s.gl_pathv)))
  {
    globfree(&glob_s);
    return (NULL);
  }
  globfree(&glob_s);
  return (tab);
}

t_arg_list		*build_spe_string(t_shell *shell, t_graph *graph)
{
  t_cmd_list		*list;
  t_cmd_list		*cmd_elem;
  t_arg_list		*arg_elem;
  int			i;

  list = NULL;
  while (graph)
  {
    i = 0;
    while (g_spe_str_dico[i].f && strcmp(g_spe_str_dico[i].rule, graph->rule))
      ++i;
    if (!g_spe_str_dico[i].f)
      return (NULL);
    if ((arg_elem = g_spe_str_dico[i].f(shell, graph->detail)))
    {
      if (!(cmd_elem = malloc(sizeof(t_cmd_list))))
	return (the_puterror(ERR_MSG_MALLOC, NULL));
      *cmd_elem = (t_cmd_list){arg_elem, NULL};
      the_pushback((void**)&list, cmd_elem, offsetof(t_cmd_list, next));
    }
    graph = graph->next;
  }
  return (the_concat(list));
}

t_cmd			*build_cmd(t_shell *shell, t_graph *graph)
{
  t_cmd			*cmd;
  t_arg_list		*arg_list;

  if (!(cmd = malloc(sizeof(t_cmd)))
      || !(arg_list = malloc(sizeof(t_cmd_list))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  memset(cmd, 0, sizeof(t_cmd));
  if (!graph || strcmp(PARSER_COMP_STRING, graph->rule))
    return (NULL);
  arg_list = build_comp_string(shell, graph->detail);
  graph = graph->next;
  while (graph)
  {
    if (!strcmp(PARSER_SPE_STRING, graph->rule))
      the_pushback((void **)&arg_list, build_spe_string(shell, graph->detail),
		   offsetof(t_arg_list, next));
    else if (!strcmp(PARSER_REDIR, graph->rule))
      the_pushback((void **)&cmd->redir_list, build_redir(shell, graph->detail),
		   offsetof(t_redir_list, next));
    graph = graph->next;
  }
  cmd->tab = build_glob(arg_list);
  return (cmd);
}
