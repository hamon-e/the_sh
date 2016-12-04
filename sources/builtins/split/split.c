/*
** split.c for PSU_2015_42sh in sources/builtins/split
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:54:12 2016 Nicolas Goudal
** Last update Thu Dec 01 10:45:28 2016
*/

#include <stdbool.h>
#include <stdio.h>
#include "tools/tools.h"

bool		the_split(int argc, char const *argv[])
{
  int		i;

  if (!argv[1] || !argv[2])
    return (false);
  i = 0;
  while (argv[2][i])
  {
    if (argv[2][i] == argv[1][0])
      while (argv[2][i] == argv[1][0])
	++i;
    else
    {
      printf("%c", argv[2][i++]);
      if (argv[2][i] == argv[1][0])
	printf("\n");
    }
  }
  return (true);
}
