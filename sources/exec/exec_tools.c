/*
** exec_tools.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:54:13 2016 Nicolas Goudal
** Last update Thu Dec 01 15:36:47 2016
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

bool		exec_reset_fd(int *fd_save)
{
  int		i;

  i = 0;
  while (i < 3)
  {
    if (fd_save[i] != -1 && dup2(fd_save[i], i) == -1)
      return (false);
    ++i;
  }
  remove(TMP_FILE);
  return (true);
}
