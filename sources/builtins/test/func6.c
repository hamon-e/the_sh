/*
** func6.c for PSU_2015_42sh in sources/builtins/test
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:40:47 2016 Nicolas Goudal
** Last update Sun Jun 05 20:41:13 2016 Nicolas Goudal
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

bool		test_p(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISFIFO(buffer.st_mode));
}

bool		test_r(char const **str)
{
  if (access(str[1], F_OK | R_OK) == -1)
    return (false);
  return (true);
}

bool		test_s(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (buffer.st_size > 0);
}

bool		test_S(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISSOCK(buffer.st_mode));
}
