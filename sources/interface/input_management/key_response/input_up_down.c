/*
** input_up_down.c for PSU_2015_42sh in sources/ncurses/input_management/key_response
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:27:56 2016 Nicolas Goudal
** Last update Thu Dec 01 11:02:33 2016
*/

#include <string.h>
#include "interface/interface.h"

static void	input_set_historic_completion(t_interface *interface,
					      t_historic_cmd_list *cmd,
					      char const *aff)
{
  interface->historic.selected = cmd;
  if (!cmd)
  {
    interface->read_buf.completion.type = NO_COMPL;
    interface->read_buf.completion.str = NULL;
  }
  else
  {
    interface->read_buf.completion.type = HISTO_COMPL;
    interface->read_buf.completion.str = cmd->str;
    if ((interface->read_buf.completion.aff = aff))
      interface->read_buf.completion.aff_len = interface->read_buf.cmd.idx;
    interface->read_buf.completion.len = strlen(cmd->str);
  }
  interface->read_buf.cursor.x = 0;
}

static void		input_down_next_strstr(t_interface *interface)
{
  t_historic_cmd_list	*cmd_list;
  char			*aff;

  cmd_list = interface->historic.selected->prev;
  while (cmd_list)
  {
    if ((aff = strstr(cmd_list->str, interface->read_buf.cmd.buf)))
    {
      input_set_historic_completion(interface, cmd_list, aff);
      return ;
    }
    cmd_list = cmd_list->prev;
  }
  interface->historic.selected = NULL;
  interface->read_buf.completion.str = NULL;
}

t_istatus		input_down_arrow_response(t_interface *interface)
{
  if (!interface->historic.cur
      || (!interface->historic.selected
	  && !(interface->historic.selected = interface->historic.cur->cmd)))
    return (S_SUCCESS);
  if (!interface->read_buf.cmd.idx)
  {
    interface->historic.selected = interface->historic.selected->prev;
    input_set_historic_completion(interface,
				  interface->historic.selected, NULL);
  }
  else
    input_down_next_strstr(interface);
  return (S_SUCCESS);
}

static void	input_up_next_strstr(t_interface *interface,
				     t_historic_cmd_list *cmd_list)
{
  char const	*aff;

  while (cmd_list)
  {
    if ((aff = strstr(cmd_list->str, interface->read_buf.cmd.buf)))
    {
      input_set_historic_completion(interface, cmd_list, aff);
      return ;
    }
    cmd_list = cmd_list->next;
  }
}

t_istatus			input_up_arrow_response(t_interface *interface)
{
  if (!interface->historic.cur
      || !interface->historic.cur->cmd)
    return (S_SUCCESS);
  if (!interface->read_buf.cmd.idx)
  {
    if (!interface->historic.selected)
      interface->historic.selected = interface->historic.cur->cmd;
    else if (interface->historic.selected->next)
      interface->historic.selected = interface->historic.selected->next;
    input_set_historic_completion(interface,
				  interface->historic.selected, NULL);
  }
  else if (!interface->historic.selected)
    input_up_next_strstr(interface, interface->historic.cur->cmd);
  else if (interface->historic.selected->next)
    input_up_next_strstr(interface, interface->historic.selected->next);
  return (S_SUCCESS);
}
