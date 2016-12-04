/*
** builtins.c for PSU_2015_42sh in sources/builtins
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 01:39:23 2016 Benoit Hamon
** Last update Thu Dec 01 15:34:49 2016
*/

#include <stdbool.h>
#include <string.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/builtins_private.h"

t_builtin_func		g_builtin_dico[] =
{
  {"set_color", the_set_color},
  {"split", the_split},
  {"echo", the_echo},
  {"test", test},
  {"set", the_set},
  {"exit", the_exit},
  {"cd", the_cd},
  {"command", command},
  {"complete", the_complete},
  {NULL, NULL}
};

bool		is_builtin(char const *cmd)
{
  int		i;

  i = 0;
  while (g_builtin_dico[i].f && strcmp(g_builtin_dico[i].cmd, cmd))
    ++i;
  return (g_builtin_dico[i].f ? true : false);
}

bool		exec_builtin(int argc,
			     char const **argv,
			     void *shell)
{
  int		i;

  i = 0;
  while (g_builtin_dico[i].f && strcmp(g_builtin_dico[i].cmd, *argv))
    ++i;
  return (g_builtin_dico[i].f(argc, argv, shell));
}
