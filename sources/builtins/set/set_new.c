/*
** set_new.c for PSU_2015_42sh in sources/builtins/set
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:51:04 2016 Nicolas Goudal
** Last update Thu Dec 01 15:34:15 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "builtins/set.h"
#include "builtins/set_private.h"
#include "builtins/builtins_msg.h"

static t_status		create_new_variables(t_var_ctrl **scope,
					     t_opt_name *name_list)
{
  int			index;
  t_var			*new_var;

  index = 1;
  if (!(*scope = malloc(sizeof(t_var_ctrl))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  memset(*scope, 0, sizeof(t_var_ctrl));
  while (name_list)
  {
    if (!(new_var = malloc(sizeof(t_var)))
	|| !(new_var->value = strdup(name_list->str)))
      return (the_putserror(ERR_MSG_MALLOC, NULL));
    new_var->index = index++;
    new_var->next = NULL;
    the_pushback((void **)&(*scope)->list, new_var, offsetof(t_var, next));
    name_list = name_list->next;
  }
  (*scope)->nbr = the_count((*scope)->list, offsetof(t_var, next));
  return (SUCCESS);
}

static t_status		add_value_at_index(t_opt_name *name_list,
					   t_var_ctrl **scope,
					   int const index)
{
  t_var			*new_var;

  if (!*scope)
  {
    if (!(*scope = malloc(sizeof(t_var_ctrl))))
      return (the_putserror(ERR_MSG_MALLOC, NULL));
    memset(*scope, 0, sizeof(t_var_ctrl));
  }
  if (!(new_var = malloc(sizeof(t_var))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  new_var->index = index;
  if (index < 0)
    new_var->index += (*scope)->nbr + 1;
  if (new_var->index <= 0)
    return (the_putserror(SET_ERR SET_WRONG_INDEX, NULL));
  if (!(new_var->value = strdup(name_list->str)))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  the_push_at_index(*scope, new_var);
  return (SUCCESS);
}

static t_status		add_new_variable(t_shell *shell,
					 t_opt const *opt,
					 char const *name,
					 int const index)
{
  t_var_list		*new_var;
  t_var_ctrl		**scope;

  if (index && opt->name->next->next)
    return (the_putserror(SET_USAGE, NULL));
  if (!(new_var = malloc(sizeof(t_var_list))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  *new_var = (t_var_list){name, NULL, NULL, NULL, NULL};
  scope = set_get_scope(new_var, name, opt->bit);
  if (!index
      && !!create_new_variables(scope, opt->name->next))
    return (FAILURE);
  else if (index
	   && !!add_value_at_index(opt->name->next, scope, index))
    return (FAILURE);
  the_pushback((void **)&shell->var, new_var, offsetof(t_var_list, next));
  return (SUCCESS);
}

static t_status		add_value_to_variable(t_opt_name *name_list,
					      t_var_ctrl **scope,
					      int const index)
{
  if (index && !name_list->next)
  {
    if (!!add_value_at_index(name_list, scope, index))
      return (FAILURE);
  }
  else if (!index && name_list)
  {
    if (*scope)
    {
      free_var_list((*scope)->list);
      free(*scope);
      *scope = NULL;
    }
    if (!!create_new_variables(scope, name_list))
      return (FAILURE);
  }
  else
    return (FAILURE);
  return (SUCCESS);
}

t_status		set_new(t_opt const *opt, t_shell *shell)
{
  int			index;
  char			*name;
  t_var_ctrl		**scope;

  if (!opt->name->next || !(name = set_get_name(opt->name->str, &index)))
    return (FAILURE);
  if (!(scope = set_get_scope(shell->var, name, opt->bit)))
  {
    if  (!!add_new_variable(shell, opt, name, index))
      return (FAILURE);
  }
  else
    if (!!add_value_to_variable(opt->name->next, scope, index))
      return (FAILURE);
  the_free(1, FREE_TAB, shell->env);
  return (!(shell->env = recreate_env(shell->var)) ? FAILURE : SUCCESS);
}
