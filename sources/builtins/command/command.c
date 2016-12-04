/*
** command.c for PSU_2015_42sh in sources/builtins/command
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Jun 04 23:37:28 2016 Benoit Hamon
** Last update Thu Dec 01 15:33:55 2016
*/

#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/exec.h"

bool		command(int argc, char const *argv[], t_shell *shell)
{
  return (exec_pbinary(argc - 1, argv + 1, shell));
}
