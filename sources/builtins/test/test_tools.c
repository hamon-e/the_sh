/*
** test_tools.c for PSU_2015_42sh in sources/builtins/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 10:21:21 2016 Benoit Hamon
** Last update Thu Dec 01 10:44:04 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "builtins/test.h"

t_tree		*test_create_node(t_test_type type,
				  char const **cmd,
				  t_tree *left,
				  t_tree *right)
{
  t_tree	*node;

  if (!(node = malloc(sizeof(t_tree))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  *node = (t_tree){type, false, cmd, NULL, left, right};
  return (node);
}
