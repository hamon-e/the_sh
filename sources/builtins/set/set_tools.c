/*
** set_tools.c for PSU_2015_42sh in sources/builtins/set
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:52:58 2016 Nicolas Goudal
** Last update Sun Dec 04 17:09:44 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/functions.h"
#include "builtins/set_private.h"
#include "builtins/builtins_msg.h"

void		*set_get_default_scope(t_var_list *var)
{
  if (var->local)
    return (&var->local);
  if (var->global)
    return (&var->global);
  if (var->export)
    return (&var->export);
  return (&var->local);
}

void		*set_get_scope(t_var_list *var, char const *str, int opt)
{
  while (var)
  {
    if (!strcmp(var->name, str))
    {
      if ((opt & OPT_LOCAL) == OPT_LOCAL)
	return (&var->local);
      else if ((opt & OPT_GLOBAL) == OPT_GLOBAL)
	return (&var->global);
      else if ((opt & OPT_EXPORT) == OPT_EXPORT)
	return (&var->export);
      else
	return (set_get_default_scope(var));
    }
    var = var->next;
  }
  return (NULL);
}

t_status		check_index(char const *str, int *n)
{
  int			index;
  int			neg;

  index = 0;
  neg = 1;
  if (str[index] == '-')
  {
    neg = -neg;
    ++index;
  }
  while (str[index] && str[index] >= '0' && str[index] <= '9')
  {
    *n = *n * 10 + str[index] - '0';
    ++index;
  }
  if (str[index] != ']' || str[index + 1] || !*n)
    return (the_putserror(SET_ERR SET_USAGE, NULL));
  *n = *n * neg;
  return (SUCCESS);
}

char			*set_get_name(char const *str, int *n)
{
  char			*name;
  int			i;

  *n = 0;
  i = 0;
  while (str[i] && (str[i] >= 'A' && str[i] <= 'Z'
		    || str[i] >= 'a' && str[i] <= 'z'))
    ++i;
  if (str[i] == '[')
  {
    if (!!check_index(str + i + 1, n))
      return (NULL);
  }
  else if (str[i])
    return (the_puterror(SET_ERR SET_USAGE, NULL));
  name = strndup(str, i);
  return (name);
}
