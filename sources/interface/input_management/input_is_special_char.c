/*
** input_is_special_char.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:25:26 2016 Nicolas Goudal
** Last update Thu Dec 01 11:01:24 2016
*/

#include <term.h>
#include <termios.h>
#include <string.h>
#include "interface/interface_private.h"
#include "interface/escape_sequence_response.h"
#include "interface/input_private.h"

/*
** reset cursor position
** reset 'read_buf->cmd.buf'
*/
static t_istatus		input_reset_line(t_interface *interface)
{
  tputs(interface->esc_seq.output[ESOUT_CLEAR_BELOW], 1, the_putchar);
  memset(interface->read_buf.cmd.buf, 0, interface->read_buf.cmd.idx);
  interface->historic.selected = NULL;
  memset(&interface->read_buf.completion, 0, sizeof(t_cmd_completion));
  interface->read_buf.cursor.x = 0;
  interface->read_buf.cursor.y = 0;
  interface->read_buf.cmd.idx = 0;
  return (S_SUCCESS);
}

/*
** return S_STOP if no other char input in order to stop
** the interface
** else return S_SUCCESS
*/
static t_istatus	input_end_of_file(t_interface *interface,
					  t_istatus *status)
{
  if (!interface->read_buf.cmd.idx && !interface->read_buf.completion.str)
    *status = S_STOP;
  return (S_SUCCESS);
}

/*
** erase one character
*/
static t_istatus		input_erase(t_interface *interface)
{
  input_delete_response(interface);
  return (S_SUCCESS);
}

static t_istatus		input_check_special_char(t_interface *interface,
							 char c,
							 t_istatus *status)
{
  int				i;
  static t_special_char_func	special_char_dico[] =
  {
    {1, input_home_response},
    {5, input_end_line_response},
    {12, input_reset_line},
    {'\t', input_completion_response}
  };

  i = 0;
  while (i < 4)
  {
    if (c == special_char_dico[i].spe_char)
    {
      if (special_char_dico[i].func)
	return (special_char_dico[i].func(interface, status));
      else
	return (S_SUCCESS);
    }
    ++i;
  }
  return (S_FAILURE);
}

/*
** check if 'c' is a special_char
*/
t_istatus			input_is_special_char(t_interface *interface,
						      char c,
						      t_istatus *status,
						      struct termios *term)
{
  int				i;
  static t_special_char_func	special_char_dico[] =
  {
    {VKILL, &input_reset_line},
    {VINTR, &input_reset_line},
    {VERASE, &input_erase},
    {VEOF, &input_end_of_file},
    {VQUIT, 0}
  };

  i = 0;
  *status = S_FAILURE;
  while (i < 4)
  {
    if (c == term->c_cc[special_char_dico[i].spe_char])
    {
      if (special_char_dico[i].func)
	return (special_char_dico[i].func(interface, status));
      else
	return (S_SUCCESS);
    }
    ++i;
  }
  return (input_check_special_char(interface, c, status));
}
