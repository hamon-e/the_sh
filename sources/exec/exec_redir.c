/*
** exec_redir.c for PSU_2015_42sh in sources/exec
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Fri Jun 03 14:29:03 2016 Benoit Hamon
** Last update Thu Dec 01 15:36:21 2016
*/

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

bool		exec_redir_right(t_redir_list *redir, int *fd_save)
{
  int		fd;
  int		nbr;

  nbr = redir->fd == -1 ? 1 : redir->fd;
  if ((fd = open(redir->name,
		 O_CREAT | O_WRONLY | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
  {
    the_puterror(ERR_MSG_OPEN, redir->name);
    return (false);
  }
  if (fd_save[nbr] == -1 && (fd_save[nbr] = dup(nbr)) == -1)
    return (false);
  if (dup2(fd, nbr) == -1
      || close(fd) == -1)
    return (false);
  return (true);
}

bool		exec_redir_left(t_redir_list *redir, int *fd_save)
{
  int		fd;

  if ((fd = open(redir->name, O_RDONLY)) == -1)
  {
    the_puterror(ERR_MSG_OPEN, redir->name);
    return (false);
  }
  if (fd_save[0] == -1 && (fd_save[0] = dup(0)) == -1)
    return (false);
  if (dup2(fd, 0) == -1
      || close(fd) == -1)
    return (false);
  return (true);
}

bool		exec_redir_double_right(t_redir_list *redir, int *fd_save)
{
  int		fd;
  int		nbr;

  nbr = redir->fd == -1 ? 1 : redir->fd;
  if ((fd = open(redir->name,
		 O_CREAT | O_WRONLY | O_APPEND,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
  {
    the_puterror(ERR_MSG_OPEN, redir->name);
    return (false);
  }
  if (fd_save[nbr] == -1 && (fd_save[nbr] = dup(nbr)) == -1)
    return (false);
  if (dup2(fd, nbr) == -1
      || close(fd) == -1)
    return (false);
  return (true);
}

bool		exec_redir_double_left(t_redir_list *redir, int *fd_save)
{
  int		fd;
  char		*input;

  if ((fd = open(TMP_FILE, O_CREAT | O_RDWR, 0666)) == -1)
  {
    the_puterror(ERR_MSG_OPEN, redir->name);
    return (false);
  }
  if (fd_save[0] == -1 && (fd_save[0] = dup(0)) == -1)
    return (false);
  while ((input = get_next_line(0)) && strcmp(input, redir->name))
  {
    dprintf(fd, "%s\n", input);
    free(input);
  }
  if (lseek(fd, 0, SEEK_SET) == -1
      || dup2(fd, 0)
      || close(fd) == -1)
    return (false);
  return (true);
}

static const t_exec_redir_func		g_redir_dico[] =
{
  {REDIR_LEFT, exec_redir_left},
  {REDIR_RIGHT, exec_redir_right},
  {REDIR_DOUBLE_LEFT, exec_redir_double_left},
  {REDIR_DOUBLE_RIGHT, exec_redir_double_right},
};

bool		exec_redir(t_redir_list *redir, int *fd_save)
{
  int		i;

  i = 0;
  while (i < 3)
  {
    fd_save[i] = -1;
    ++i;
  }
  while (redir)
  {
    i = 0;
    while (g_redir_dico[i].type != redir->type)
      ++i;
    if (!g_redir_dico[i].f(redir, fd_save))
      return (false);
    redir = redir->next;
  }
  return (true);
}
