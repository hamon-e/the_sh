/*
** func5.c for PSU_2015_42sh in sources/builtins/test
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:39:42 2016 Nicolas Goudal
** Last update Sun Jun 05 20:40:42 2016 Nicolas Goudal
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

bool		test_f(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISREG(buffer.st_mode));
}

bool		test_g(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (buffer.st_mode & S_ISGID);
}

bool		test_G(char const **str)
{
  struct stat	buffer;
  uid_t		nbr;

  if (stat(str[1], &buffer) == -1)
    return (false);
  nbr = getgid();
  return (buffer.st_gid == nbr);
}

bool		test_L(char const **str)
{
  struct stat	buffer;

  if (stat(str[1], &buffer) == -1)
    return (false);
  return (S_ISLNK(buffer.st_mode));
}

bool		test_O(char const **str)
{
  struct stat	buffer;
  uid_t		nbr;

  if (stat(str[1], &buffer) == -1)
    return (false);
  nbr = getuid();
  return (buffer.st_uid == nbr);
}
