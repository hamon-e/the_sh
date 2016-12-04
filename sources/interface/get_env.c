/*
** get_env.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:19:42 2016 Nicolas Goudal
** Last update Sun Jun 05 23:19:43 2016 Nicolas Goudal
*/

#include <string.h>

static char	*get_env_val(char const *str)
{
  int		i;
  char		*val;

  i = 0;
  while (str[i] && str[i] != ':')
    ++i;
  if (!i)
    return (NULL);
  return ((val = strndup(str, i)));
}

char		*get_env(char const *env[],
			 char const *var)
{
  int		i;
  int		length;

  length = strlen(var);
  i = 0;
  while (env[i])
  {
    if (!strncmp(var, env[i], length))
      return (get_env_val(env[i] + length));
    ++i;
  }
  return (NULL);
}
