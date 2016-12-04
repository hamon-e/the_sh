/*
** free_list_index.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:29:58 2016 Nicolas Goudal
** Last update Sun Dec 04 17:11:17 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

void		*free_list_index(t_index_list *list)
{
  if (list)
  {
    free_list_index(list->next);
    free(list);
  }
  return (NULL);
}
