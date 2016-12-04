/*
** base_to_ascii.c for PSU_2015_42sh in sources/tools
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:25:02 2016 Nicolas Goudal
** Last update Thu Dec 01 11:21:17 2016
*/

#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"

static t_status		get_nbr_in_base(char const c,
					char const *str,
					int *n)
{
  *n = 0;
  while (str[*n] && str[*n] != c)
    ++(*n);
  return (!str[*n] ? FAILURE : SUCCESS);
}

int			base_to_ascii(char const *word,
				      char const *base,
				      int *i)
{
  size_t		base_size;
  int			res;
  int			index;
  int			j;

  res = 0;
  index = *i + 2;
  base_size = strlen(base);
  while (word[index]
	 && !get_nbr_in_base((word[index] >= 'a' && word[index] <= 'z'
			      ? word[index] - 32 : word[index]), base, &j))
  {
    res *= base_size;
    res += j;
    ++(index);
  }
  if (index != *i + 2)
    *i = index;
  else
    return (-1);
  return (res);
}
