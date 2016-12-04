/*
** interface_quit.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:20:47 2016 Nicolas Goudal
** Last update Thu Dec 01 11:00:34 2016
*/

#include <unistd.h>
#include <ncurses.h>
#include <term.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interface/interface.h"

/*
** free historic
*/
void			interface_quit_free_historic(t_historic *historic)
{
  t_historic_dir_list	*dir_list;
  t_historic_cmd_list	*cmd_list;
  void			*swap;

  if (historic->fd != -1)
    close(historic->fd);
  dir_list = historic->dir;
  while (dir_list)
  {
    cmd_list = dir_list->cmd;
    while (cmd_list)
    {
      swap = cmd_list;
      free(cmd_list->str);
      cmd_list = cmd_list->next;
      free(swap);
    }
    swap = dir_list;
    free(dir_list->name);
    dir_list = dir_list->next;
    free(swap);
  }
}

/*
** clear cursor
** make cursor visible
** free buffer
** free historic
*/
void			interface_quit(t_interface *interface,
				       bool is_new_cmd)
{
  if (!is_new_cmd)
    interface_print(interface, B_FALSE);
  the_putstr(1, "\n");
  tputs(interface->esc_seq.output[ESOUT_CURSOR_VIS], 0, &the_putchar);
  free(interface->read_buf.cmd.buf);
  free(interface->read_buf.input.buf);
  del_curterm(cur_term);
  interface_quit_free_historic(&interface->historic);
}
