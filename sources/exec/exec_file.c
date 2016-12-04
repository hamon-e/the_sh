/*
** exec_file.c for PSU_2015_42sh in sources/exec
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:56:29 2016 Nicolas Goudal
** Last update Thu Dec 01 20:09:14 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "tools/tools.h"
#include "tools/msg.h"
#include "opt_parser/opt.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/init_shell.h"

void			exec_file(t_shell *shell,
				  char const *file)
{
  struct stat		buf;
  int			fd;
  char			*str;

  if (!file
      || (fd = open(file, O_RDONLY)) == -1
      || (stat(file, &buf)) == -1)
  {
    the_puterror(ERR_MSG_OPEN, file);
    return ;
  }
  if (!(str = malloc(sizeof(char) * (buf.st_size + 1))))
  {
    the_puterror(ERR_MSG_MALLOC, NULL);
    return ;
  }
  if (read(fd, str, buf.st_size) != buf.st_size)
  {
    the_puterror(ERR_MSG_READ, file);
    return ;
  }
  close(fd);
  str[buf.st_size] = '\0';
  shell_loop(shell, NULL, str);
  free(str);
}
