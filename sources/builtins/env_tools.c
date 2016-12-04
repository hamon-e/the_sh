/*
** env_tools.c for PSU_2015_42sh in sources/builtins
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:44:18 2016 Nicolas Goudal
** Last update Thu Dec 01 15:34:01 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "builtins/builtins_msg.h"

static char	*update_env_var(t_var *list, char const *name)
{
  size_t	tab_length;
  char		*new_var;
  t_var		*tmp;

  tab_length = strlen(name);
  tmp = list;
  while (tmp)
  {
    tab_length += strlen(tmp->value) + 1;
    tmp = tmp->next;
  }
  if (!(new_var = malloc(sizeof(char) * (tab_length + 1))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  new_var = strcpy(new_var, name);
  new_var = strcat(new_var, "=");
  new_var = strcat(new_var, list->value);
  list = list->next;
  while (list)
  {
    new_var = strcat(new_var, ":");
    new_var = strcat(new_var, list->value);
    list = list->next;
  }
  return (new_var);
}

char		**recreate_env(t_var_list *var_list)
{
  size_t	tab_length;
  char		**new_env;
  t_var_list	*tmp;

  tab_length = 0;
  tmp = var_list;
  while (tmp)
  {
    if (tmp->export)
      ++tab_length;
    tmp = tmp->next;
  }
  if (!(new_env = malloc(sizeof(char *) * (tab_length + 1))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  tab_length = 0;
  while (var_list)
  {
    if (var_list->export)
      if (!(new_env[tab_length++]
	    = update_env_var(var_list->export->list, var_list->name)))
	return (NULL);
    var_list = var_list->next;
  }
  new_env[tab_length] = NULL;
  return (new_env);
}

t_status	find_env_var(char **env, char const *name, int *index)
{
  size_t	name_length;

  *index = 0;
  name_length = strlen(name);
  while (env[*index] && strncmp(env[*index], name, name_length))
    ++(*index);
  if (!env[*index])
    return (the_putserror(NO_ENV_VAR, name));
  return (SUCCESS);
}
