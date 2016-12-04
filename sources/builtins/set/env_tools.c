/*
** env_tools.c for PSU_2015_42sh in sources/builtins/set
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:49:14 2016 Nicolas Goudal
** Last update Thu Dec 01 15:34:44 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/functions.h"

static char	*update_env_var(t_var *list, char const *name)
{
  size_t	length;
  char		*new_var;
  t_var		*tmp;

  length = strlen(name);
  tmp = list;
  while (tmp)
  {
    length += strlen(tmp->value) + 1;
    tmp = tmp->next;
  }
  if (!(new_var = malloc(sizeof(char) * (length + 1))))
    return (NULL);
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
  size_t	length;
  char		**new_env;
  t_var_list	*tmp;

  length = 0;
  tmp = var_list;
  while (tmp)
  {
    if (tmp->export)
      ++length;
    tmp = tmp->next;
  }
  if (!(new_env = malloc(sizeof(char *) * (length + 1))))
    return (NULL);
  length = 0;
  while (var_list)
  {
    if (var_list->export)
      if (!(new_env[length++]
	    = update_env_var(var_list->export->list, var_list->name)))
	return (NULL);
    var_list = var_list->next;
  }
  new_env[length] = NULL;
  return (new_env);
}
