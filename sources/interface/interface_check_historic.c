/*
** interface_check_historic.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:22:35 2016 Nicolas Goudal
** Last update Thu Dec 01 10:59:14 2016
*/

#include <string.h>
#include "interface/interface_private.h"
#include "interface/historic_private.h"

void			interface_check_historic(t_interface *interface)
{
  t_historic_cmd_list	*list;
  int			len;
  int			len2;

  if (!interface->read_buf.cmd.idx || interface->read_buf.completion.str
      || !interface->historic.cur || !interface->historic.cur->cmd)
    return ;
  interface->read_buf.completion.aff = NULL;
  interface->read_buf.completion.type = NO_COMPL;
  list = interface->historic.cur->cmd;
  while (list)
  {
    if (!strncmp(interface->read_buf.cmd.buf, list->str,
		 (len = the_strlen(interface->read_buf.cmd.buf)))
	&& (len2 = the_strlen(list->str)) > len)
    {
      interface->read_buf.completion.type = LINE_COMPL;
      interface->read_buf.completion.aff = list->str + len;
      interface->read_buf.completion.aff_len = len2 - len;
      interface->read_buf.completion.len
	= interface->read_buf.completion.aff_len;
      return ;
    }
    list = list->next;
  }
}
