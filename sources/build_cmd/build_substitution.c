/*
** build_substitution.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:32:19 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:50 2016
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/exec.h"

static void		free_subsitution(t_arg_list *list)
{
  if (list)
  {
    free_subsitution(list->next);
    free(list);
  }
}

static t_arg_list	*build_substitution_index(t_arg_list *list,
						  t_index_list *index,
						  int max)
{
  t_arg_list		*tmp;
  t_arg_list		*elem;
  int			i;

  tmp = NULL;
  i = 1;
  while (list)
  {
    if (keep_index(index, max, i))
    {
      if (!(elem = malloc(sizeof(t_arg_list))))
	return (the_puterror(ERR_MSG_MALLOC, NULL));
      elem->str = list->str;
      elem->next = NULL;
      the_pushback((void **)&tmp, elem, offsetof(t_arg_list, next));
    }
    else
      free(list->str);
    list = list->next;
    ++i;
  }
  free_subsitution(list);
  return (tmp);
}

static t_arg_list	*build_substitution_father(t_index_list *index,
						   int pid,
						   int *fd)
{
  char			*str;
  int			max;
  t_arg_list		*list;
  t_arg_list		*elem;

  if (close(fd[1]) == -1)
    return (NULL);
  list = NULL;
  max = 1;
  while ((str = get_next_line(fd[0])))
  {
    if (!(elem = malloc(sizeof(t_arg_list))))
      return (NULL);
    elem->str = str;
    elem->next = NULL;
    ++max;
    the_pushback((void **)&list, elem, offsetof(t_arg_list, next));
  }
  if (waitpid(pid, NULL, 0) == -1)
    return (NULL);
  return (list ? build_substitution_index(list, index, max) : list);
}

t_arg_list		*build_substitution(t_shell *shell, t_graph *graph)
{
  t_arg_list		*list;
  t_index_list		*index;
  int			pid;
  int			fd[2];

  if (!graph
      || pipe(fd) == -1
      || (pid = fork()) == -1)
    return (NULL);
  if (!pid)
  {
    if (close(fd[0]) != -1
	&& dup2(fd[1], 1) != -1)
      exec(shell, graph->detail);
    exit(0);
  }
  else
  {
    index = graph->next ? build_index(graph->next->detail) : NULL;
    list = build_substitution_father(index, pid, fd);
    the_free(1, FREE_LST_INDEX, index);
    return (list);
  }
}
