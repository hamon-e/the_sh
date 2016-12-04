/*
** set_color.c for PSU_2015_42sh in sources/builtins/set_color
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:53:41 2016 Nicolas Goudal
** Last update Thu Dec 01 10:45:56 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "interface/color.h"
#include "builtins/builtins_msg.h"

static const t_color_set_tab	g_color_tab[] =
{
  {"\x1b[1;30m", "\x1b[1;40m", "black"},
  {"\x1b[1;31m", "\x1b[1;41m", "red"},
  {"\x1b[1;32m", "\x1b[1;42m", "green"},
  {"\x1b[1;33m", "\x1b[1;43m", "yellow"},
  {"\x1b[1;34m", "\x1b[1;44m", "blue"},
  {"\x1b[1;35m", "\x1b[1;45m", "magenta"},
  {"\x1b[1;36m", "\x1b[1;46m", "cyan"},
  {"\x1b[1;37m", "\x1b[1;47m", "white"},
  {"\x1b[1;90m", "\x1b[1;100m", "dgray"},
  {"\x1b[1;91m", "\x1b[1;101m", "lred"},
  {"\x1b[1;92m", "\x1b[1;102m", "lgreen"},
  {"\x1b[1;93m", "\x1b[1;103m", "lyellow"},
  {"\x1b[1;94m", "\x1b[1;104m", "lblue"},
  {"\x1b[1;95m", "\x1b[1;105m", "lmagenta"},
  {"\x1b[1;96m", "\x1b[1;106m", "lcyan"},
  {"\x1b[1;97m", "\x1b[1;107m", "lgray"},
  {"\x1b[0m", "\x1b[0m", "reset"},
  {NULL, NULL, NULL}
};

bool				the_set_color(int argc,
					      char const *argv[])
{
  int				i;
  int				j;
  bool				fgd;

  if (!argv[0] || !argv[1])
    return (false);
  i = 0;
  j = 1;
  fgd = true;
  if (!strcmp(argv[j], "-b")
      || !strcmp(argv[j], "--background"))
  {
    ++j;
    fgd = false;
  }
  else if (argv[j][0] == '-')
    return (dprintf(2, SET_COLOR_ERR SET_COLOR_USAGE) * 0);
  while (argv[j] && g_color_tab[i].fgd && strcmp(g_color_tab[i].name, argv[j]))
    ++i;
  if (g_color_tab[i].fgd)
    fgd ? printf("%s", g_color_tab[i].fgd) : printf("%s", g_color_tab[i].bkg);
  else
    return (dprintf(2, SET_COLOR_ERR SET_COLOR_USAGE) * 0);
  fflush(stdout);
  return (true);
}
