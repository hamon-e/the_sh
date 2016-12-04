/*
** global_tools.c for PSU_2015_42sh in sources/builtins/set
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:49:46 2016 Nicolas Goudal
** Last update Thu Dec 01 15:34:08 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/find.h"
#include "builtins/set.h"
#include "builtins/set_private.h"

void			*init_new_var(t_shell *shell,
				      char const *name,
				      t_opt_bit bit)
{
  t_var_ctrl		**scope;
  t_var_list		*new_var;

  if (!(scope = set_get_scope(shell->var, name, bit)))
  {
    if (!(new_var = malloc(sizeof(t_var_list))))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    *new_var = (t_var_list){name, NULL, NULL, NULL, NULL};
    if (!(scope = set_get_scope(new_var, name, bit)))
      return (NULL);
    the_pushback((void **)&shell->var, new_var, offsetof(t_var_list, next));
  }
  else
    if (*scope && (*scope)->list)
      free_var_list((*scope)->list);
  if (!(*scope = malloc(sizeof(t_var_ctrl))))
    return (NULL);
  (*scope)->list = NULL;
  return (scope);
}

t_status		add_tab_var_local(t_shell *shell,
					  char const *name,
					  char const **value)
{
  int			i;
  t_var			*new_value;
  t_var_ctrl		**scope;

  if (!value || !(scope = init_new_var(shell, name, OPT_LOCAL)))
    return (FAILURE);
  i = 0;
  while (value[i])
  {
    if (!(new_value = malloc(sizeof(t_var))))
      return (the_putserror(ERR_MSG_MALLOC, NULL));
    *new_value = (t_var){strdup(value[i]), ++i, NULL};
    the_pushback((void **)&(*scope)->list, new_value, offsetof(t_var, next));
  }
  (*scope)->nbr = i;
  return (SUCCESS);
}

t_status		add_int_var_global(t_shell *shell,
					   char const *name,
					   int value)
{
  t_var			*new_value;
  t_var_ctrl		**scope;

  if (!(scope = init_new_var(shell, name, OPT_GLOBAL)))
    return (FAILURE);
  if (!(new_value = malloc(sizeof(t_var))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  *new_value = (t_var){the_itoa(value), 1, NULL};
  (*scope)->list = new_value;
  (*scope)->nbr = 1;
  return (SUCCESS);
}

t_status		add_string_var_export(t_shell *shell,
					      char const *name,
					      char const *value)
{
  t_var			*new_value;
  t_var_ctrl		**scope;

  if (!value || !(scope = init_new_var(shell, name, OPT_EXPORT)))
    return (FAILURE);
  if (!(new_value = malloc(sizeof(t_var))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  *new_value = (t_var){strdup(value), 1, NULL};
  (*scope)->list = new_value;
  (*scope)->nbr = 1;
  the_free(1, FREE_TAB, shell->env);
  return (!(shell->env = recreate_env(shell->var)) ? FAILURE : SUCCESS);
}

t_status		add_string_var_local(t_shell *shell,
					     char const *name,
					     char const *value)
{
  t_var			*new_value;
  t_var_ctrl		**scope;

  if (!value || !(scope = init_new_var(shell, name, OPT_LOCAL)))
    return (FAILURE);
  if (!(new_value = malloc(sizeof(t_var))))
    return (the_putserror(ERR_MSG_MALLOC, NULL));
  *new_value = (t_var){strdup(value), 1, NULL};
  (*scope)->list = new_value;
  (*scope)->nbr = 1;
  return (SUCCESS);
}
