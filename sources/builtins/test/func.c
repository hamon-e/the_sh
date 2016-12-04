/*
** func.c for test in /home/hamon_e/Documents/Tech/Unix/test/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Apr 16 07:29:12 2016 Benoit Hamon
** Last update Thu Dec 01 10:45:13 2016
*/

#include <stdbool.h>
#include "tools/tools.h"

bool	test_ne(char const **str)
{
  int	nbr;
  int	nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr != nbr2);
}

bool	test_gt(char const **str)
{
  int	nbr;
  int	nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr > nbr2);
}

bool	test_ge(char const **str)
{
  int	nbr;
  int	nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr >= nbr2);
}

bool	test_lt(char const **str)
{
  int	nbr;
  int	nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr < nbr2);
}

bool	test_le(char const **str)
{
  int	nbr;
  int	nbr2;

  nbr = the_atoi(str[0]);
  nbr2 = the_atoi(str[2]);
  return (nbr <= nbr2);
}
