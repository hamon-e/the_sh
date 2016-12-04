/*
** free_list_func.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:33:44 2016 Nicolas Goudal
** Last update Thu Dec 01 15:37:12 2016
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"

void		*free_list_func(t_func_list *func)
{
  t_func_list	*tmp;

  while (func)
  {
    tmp = func->next;
    the_free(2, FREE_STR, func->name, FREE_STR, func->cmd);
    free(func);
    func = tmp;
  }
  return (NULL);
}
