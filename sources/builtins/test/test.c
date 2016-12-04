/*
** test.c for test in /home/hamon_e/Documents/Tech/Unix/test/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Wed Apr 13 15:39:23 2016 Benoit Hamon
** Last update Sun Dec 04 17:13:41 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tools/tools.h"
#include "builtins/test.h"

static bool		exec(t_tree *node);

static bool		exec_or(t_tree *node)
{
  if (exec(node->left))
    return (true);
  return (exec(node->right));
}

static bool		exec_and(t_tree *node)
{
  if (exec(node->left) && exec(node->right))
    return (true);
  return (false);
}

static bool		exec(t_tree *node)
{
  bool			res;

  if (node->type == TEST_OR)
    res = exec_or(node);
  else if (node->type == TEST_AND)
    res = exec_and(node);
  else
    res = node->f(node->cmd);
  return (node->reverse ? !res : res);
}

bool			test(int argc, char const* argv[])
{
  t_tree		*tree;
  char const		**tmp;
  bool			ok;

  tmp = argv + 1;
  if (argc == 2 && *argv[1])
    return (true);
  tree = test_parser(&tmp, 0);
  if (tree)
  {
    ok = exec(tree);
    the_free(1, FREE_TEST_TREE, tree);
    return (ok);
  }
  return (false);
}
