/*
** global_tools_next.c for  in /home/gusmin_m/Unix_System_programming/PSU_2015_42sh/sources/builtins/set
**
** Made by Matthieu Gusmini
** Login   <gusmin_m@epitech.eu>
**
** Started on  Mon Jun  6 01:13:26 2016
** Last update Thu Dec 01 15:34:38 2016
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "builtins/set.h"

void			free_all_local_var(t_shell *shell)
{
  t_var_list		*tmp;

  tmp = shell->var;
  while (tmp)
  {
    if (tmp->local && tmp->local->list)
    {
      free_var_list(tmp->local->list);
      free(tmp->local);
      tmp->local = NULL;
    }
    tmp = tmp->next;
  }
}
