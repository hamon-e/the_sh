/*
** test_parser.c for PSU_2015_42sh in sources/builtins/test
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 10:23:56 2016 Benoit Hamon
** Last update Sun Dec 04 17:10:30 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <string.h>
#include "tools/tools.h"
#include "builtins/test.h"

static const t_test_func	g_test_dico[] =
{
  {"-b", 1, test_b},
  {"-c", 1, test_c},
  {"-d", 1, test_d},
  {"-e", 1, test_e},
  {"-f", 1, test_f},
  {"-g", 1, test_g},
  {"-G", 1, test_G},
  {"-L", 1, test_L},
  {"-O", 1, test_O},
  {"-p", 1, test_p},
  {"-r", 1, test_r},
  {"-s", 1, test_s},
  {"-S", 1, test_S},
  {"-t", 1, test_t},
  {"-u", 1, test_u},
  {"-w", 1, test_w},
  {"-x", 1, test_x},
  {"=", 2, test_equal},
  {"!=", 2, test_nequal},
  {"-n", 1, test_n},
  {"-z", 1, test_z},
  {"-eq", 2, test_eq},
  {"-ne", 2, test_ne},
  {"-gt", 2, test_gt},
  {"-ge", 2, test_ge},
  {"-lt", 2, test_lt},
  {"-le", 2, test_le},
  {NULL, 0, NULL}
};

static bool		test_parse_reverse(char const ***argv)
{
  char const		**tmp;
  bool			reverse;

  tmp = *argv;
  reverse = false;
  while (*tmp && !strcmp(*tmp, "!"))
  {
    reverse = !reverse;
    ++tmp;
  }
  *argv = tmp;
  return (reverse);
}

static t_tree		*test_parse_cmd(char const ***argv)
{
  char const		**tmp;
  t_tree		*node;
  int			i;

  tmp = *argv;
  i = 0;
  if (!*tmp || !*(tmp + 1))
    return (NULL);
  while (g_test_dico[i].cmd)
  {
    if ((g_test_dico[i].nbr == 1 || *(tmp + 2))
	&& !strcmp(g_test_dico[i].cmd, tmp[g_test_dico[i].nbr - 1]))
      break ;
    ++i;
  }
  if (!g_test_dico[i].cmd)
    return (NULL);
  if (!(node = test_create_node(TEST_CMD, tmp, NULL, NULL)))
    return (NULL);
  node->f = g_test_dico[i].f;
  tmp += g_test_dico[i].nbr + 1;
  *argv = tmp;
  return (node);
}

static t_tree		*test_parse_oth(char const ***argv)
{
  char const		**tmp;
  t_tree		*node;
  bool			reverse;

  tmp = *argv;
  reverse = test_parse_reverse(&tmp);
  if (*tmp && !strcmp(*tmp, "("))
  {
    ++tmp;
    if (!*tmp || !(node = test_parser(&tmp, 0)))
      return (NULL);
    if (strcmp(*tmp, ")"))
      return (the_free(1, FREE_TEST_TREE, node));
    *argv = tmp + 1;
  }
  else
  {
    if (!*tmp || !(node = test_parse_cmd(&tmp)))
      return (NULL);
    *argv = tmp;
  }
  node->reverse = reverse;
  return (node);
}

static const t_ope_func		g_dico_ope[] =
{
  {test_parser, TEST_OR, "-o"},
  {test_parser, TEST_AND, "-a"},
  {test_parse_oth, TEST_CMD, NULL}
};

t_tree			*test_parser(char const ***argv, int index)
{
  char const		**tmp;
  t_tree		*node;
  t_tree		*node1;

  tmp = *argv;
  if (!*tmp || !(node = g_dico_ope[index].f(&tmp, index + 1)))
    return (NULL);
  *argv = tmp;
  if (index == 2)
    return (node);
  while (*tmp && !strcmp(*tmp, g_dico_ope[index].cmd))
  {
    if (!(node1 = test_create_node(g_dico_ope[index].type, NULL, node, NULL)))
      return (the_free(1, FREE_TEST_TREE, node));
    ++tmp;
    if (!*tmp || !(node1->right = g_dico_ope[index].f(&tmp, index + 1)))
      return (the_free(1, FREE_TEST_TREE, node));
    *argv = tmp;
    node = node1;
  }
  return (node);
}
