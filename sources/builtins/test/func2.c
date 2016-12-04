/*
** func2.c for test in /home/hamon_e/Documents/Tech/Unix/PSU_2015_42sh/sources/builins/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Apr 16 08:19:14 2016 Benoit Hamon
** Last update Thu Dec 01 10:45:07 2016
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tools/tools.h"

bool		test_t(char const **str)
{
  int		nbr;

  nbr = the_atoi(str[1]);
  return (isatty(nbr));
}

bool		test_u(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (buffer.st_mode & S_ISUID);
}

bool		test_w(char const **str)
{
  if (access(str[1], F_OK | W_OK) == -1)
    return (false);
  return (true);
}

bool		test_x(char const **str)
{
  if (access(str[1], F_OK | X_OK) == -1)
    return (false);
  return (true);
}
