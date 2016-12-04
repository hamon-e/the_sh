/*
** set.c for PSU_2015_42sh in sources/builins/set
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu May 26 22:04:56 2016 Benoit Hamon
** Last update Thu Dec 01 15:34:32 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "builtins/set.h"
#include "builtins/set_private.h"
#include "builtins/builtins_msg.h"

static const t_opt_dico	g_opt_dico[] =
{
  {OPT_LOCAL, 'l', "local", false, 0, 0},
  {OPT_GLOBAL, 'g', "global", false, 0, 0},
  {OPT_EXPORT, 'x', "export", false, 0, 0},
  {OPT_ERASE, 'e', "erase", false, 0, 0},
  {OPT_QUERY, 'q', "query", false, 0, 0},
  {OPT_NAMES, 'n', "names", false, 0, 0},
  {0}
};

static t_status		set_print(t_var_list *var_list, int opt)
{
  t_var_ctrl		**scope;
  t_var			*tmp;

  while (var_list)
  {
    if (!(scope = set_get_scope(var_list, var_list->name, opt)))
      return (FAILURE);
    else if (*scope)
    {
      tmp = (*scope)->list;
      printf("%s ", var_list->name);
      while (tmp)
      {
	printf("%s", tmp->value);
	if (tmp->next)
	  printf(" ");
	tmp = tmp->next;
      }
      printf("\n");
    }
    var_list = var_list->next;
  }
  return (SUCCESS);
}

static t_status		set_names(t_opt const *opt, t_shell *shell)
{
  t_var_ctrl		**scope;
  t_var_list		*tmp;

  tmp = shell->var;
  while (tmp)
  {
    if (!(scope = set_get_scope(tmp, tmp->name, opt->bit)))
      return (FAILURE);
    else if (*scope && (*scope)->list)
    {
      printf("%s", tmp->name);
      printf("\n");
    }
    tmp = tmp->next;
  }
  return (SUCCESS);
}

static t_status		set_erase(t_opt const *opt, t_shell *shell)
{
  int			index;
  char			*name;
  t_var_ctrl		**scope;

  if (!opt->name || opt->name->next)
    return (the_putserror("Usage :\n", NULL));
  if (!(name = set_get_name(opt->name->str, &index))
      || !(scope = set_get_scope(shell->var, name, opt->bit)))
    return (FAILURE);
  if (index && *scope)
  {
    if (!!delete_at_index(*scope, index))
      return (FAILURE);
  }
  else if (!index && *scope)
  {
    free_var_list((*scope)->list);
    free(*scope);
    *scope = NULL;
  }
  else
    return (FAILURE);
  the_free(1, FREE_TAB, shell->env);
  return (!(shell->env = recreate_env(shell->var)) ? FAILURE : SUCCESS);
}

static t_status		set_query(t_opt const *opt, t_shell *shell)
{
  int			index;
  char			*name;
  t_var			*var_tmp;
  t_opt_name		*tmp;
  t_var_ctrl		**scope;

  tmp = opt->name;
  while (tmp)
  {
    if (!(name = set_get_name(tmp->str, &index))
	|| !(scope = set_get_scope(shell->var, name, opt->bit)))
      return (FAILURE);
    if (index)
    {
      if (index < 0)
	index += (*scope)->nbr + 1;
      var_tmp = (*scope)->list;
      while (var_tmp && var_tmp->index != index)
	var_tmp = var_tmp->next;
      if (!var_tmp)
	return (FAILURE);
    }
    tmp = tmp->next;
  }
  return (SUCCESS);
}

static const t_set_func	g_set_dico[] =
{
  {OPT_ERASE, set_erase},
  {OPT_QUERY, set_query},
  {OPT_NAMES, set_names},
  {0, NULL}
};

bool			the_set(int argc,
				char const *argv[],
				t_shell *shell)
{
  t_opt			*opt;
  int			i;

  if (!(opt = opt_init(argc, argv + 1, 0, g_opt_dico)))
  {
    dprintf(2, SET_ERR SET_USAGE);
    return (false);
  }
  i = 0;
  while (g_set_dico[i].type
	 && (g_set_dico[i].type & opt->bit) != g_set_dico[i].type)
    ++i;
  if (g_set_dico[i].type)
    return (!!g_set_dico[i].f(opt, shell) ? false : true);
  if (!opt->name)
    return (!!set_print(shell->var, opt->bit) ? false : true);
  return (!!set_new(opt, shell) ? false : true);
}
