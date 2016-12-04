/*
** complete.c for PSU_2015_42sh in /Users/florian/Desktop/epitech/B2-PSU/final/PSU_2015_42sh/sources/builtins/complete
**
** Made by Florian Guyonnet
** Login   <guyonn_f@epitech.net>
**
** Started on  Sun Jun  5 14:40:48 2016 Florian Guyonnet
** Last update Thu Dec 01 15:34:53 2016
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "complete/complete_private.h"

bool			the_complete(int argc,
                                     char const *argv[],
                                     t_shell *shell)
{
  if (argc < 2 ||
      complete_insert(argv, shell->complete) == SUCCESS)
    return (false);
  return (true);
}
