/*
** free_all.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:29:36 2016 Nicolas Goudal
** Last update Thu Dec 01 15:37:37 2016
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"

void		*free_all(t_shell *shell)
{
  the_free(3, FREE_TAB, shell->env,
	   FREE_LST_FUNC, shell->func,
	   FREE_LST_VAR, shell->var);
  free(shell->complete);
  free(shell->grammar);
  free(shell);
  return (NULL);
}
