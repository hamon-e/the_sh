/*
** color_init.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:19:35 2016 Nicolas Goudal
** Last update Thu Dec 01 10:56:31 2016
*/

#include "interface/color.h"
#include "interface/interface_private.h"

static const t_color_set	g_color_tab[] =
{
  {"\x1b[30m", "\x1b[40m"},
  {"\x1b[31m", "\x1b[41m"},
  {"\x1b[32m", "\x1b[42m"},
  {"\x1b[33m", "\x1b[43m"},
  {"\x1b[34m", "\x1b[44m"},
  {"\x1b[35m", "\x1b[45m"},
  {"\x1b[36m", "\x1b[46m"},
  {"\x1b[37m", "\x1b[47m"},
  {"\x1b[90m", "\x1b[100m"},
  {"\x1b[91m", "\x1b[101m"},
  {"\x1b[92m", "\x1b[102m"},
  {"\x1b[93m", "\x1b[103m"},
  {"\x1b[94m", "\x1b[104m"},
  {"\x1b[95m", "\x1b[105m"},
  {"\x1b[96m", "\x1b[106m"},
  {"\x1b[97m", "\x1b[107m"},
  {NULL, NULL}
};

void			interface_init_color(t_interface *interface)
{
  interface->color[DEFAULT_COLOR].fgd = g_color_tab[WHITE].fgd;
  interface->color[RESERVED_COLOR].fgd = g_color_tab[LMAGENTA].fgd;
  interface->color[COMPL_COLOR].fgd = g_color_tab[DGRAY].fgd;
  interface->color[CMD_COLOR].fgd = g_color_tab[BLUE].fgd;
  interface->color[ARG_COLOR].fgd = g_color_tab[LBLUE].fgd;
  interface->color[DQUOTE_COLOR].fgd = g_color_tab[YELLOW].fgd;
  interface->color[SQUOTE_COLOR].fgd = g_color_tab[YELLOW].fgd;
  interface->color[INHIB_COLOR].fgd = g_color_tab[LBLUE].fgd;
  interface->color[COMBINER_COLOR].fgd = g_color_tab[CYAN].fgd;
  interface->color[VAR_COLOR].fgd = g_color_tab[LGREEN].fgd;
  interface->color[UNKNOWN_COLOR].fgd = g_color_tab[RED].fgd;
}
