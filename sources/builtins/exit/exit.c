/*
** exit.c for PSU_2015_42sh in sources/builtins/exit
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Jun 04 14:34:02 2016 Benoit Hamon
** Last update Thu Dec 01 15:33:48 2016
*/

#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"

bool		the_exit(int __attribute__((unused))argc,
			 char const *argv[],
			 t_shell *shell)
{
  int		i;

  i = 0;
  while (argv[1] && argv[1][i])
  {
    if (argv[1][i] > '9' || argv[1][i] < '0')
      return (false);
    ++i;
  }
  shell->exit = the_atoi(argv[1]);
  return (true);
}
