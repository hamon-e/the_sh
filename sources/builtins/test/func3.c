/*
** func3.c for test in /home/hamon_e/Documents/Tech/Unix/PSU_2015_42sh/sources/builins/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Apr 16 09:09:58 2016 Benoit Hamon
** Last update Sun Jun 05 20:41:54 2016 Nicolas Goudal
*/

#include <string.h>
#include <stdbool.h>

bool		test_equal(char const **str)
{
  return (!strcmp(str[0], str[2]));
}

bool		test_nequal(char const **str)
{
  return (strcmp(str[0], str[2]));
}

bool		test_n(char const **str)
{
  return (strlen(str[0]) != 0);
}

bool		test_z(char const **str)
{
  return (strlen(str[0]) == 0);
}
