/*
** func4.c for PSU_2015_42sh in sources/builtins/test
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:36:57 2016 Nicolas Goudal
** Last update Thu Dec 01 10:44:57 2016
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tools/tools.h"

bool		test_eq(char const **str)
{
  int		nbr;
  int		nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr == nbr2);
}

bool		test_d(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISDIR(buffer.st_mode));
}

bool		test_b(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISBLK(buffer.st_mode));
}

bool		test_c(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISCHR(buffer.st_mode));
}

bool		test_e(char const **str)
{
  if (access(str[1], F_OK) == -1)
    return (false);
  return (true);
}
