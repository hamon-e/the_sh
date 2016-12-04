/*
** interface.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:23:08 2016 Nicolas Goudal
** Last update Thu Dec 01 15:40:49 2016
*/

#include <fcntl.h>
#include <stdlib.h>
#include <term.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "the_parser/parser.h"
#include "the_parser/rules.h"
#include "shell/shell.h"
#include "shell/find.h"
#include "shell/functions.h"
#include "interface/interface.h"
#include "interface/interface_print.h"
#include "interface/error_define.h"

/*
** set terminal
*/
static t_istatus	interface_set_term(struct termios const *term)
{
  struct termios	new;

  new = *term;
  new.c_lflag &= ~(ICANON);
  new.c_lflag &= ~(ECHO);
  new.c_lflag &= ~(ISIG);
  new.c_cc[VMIN] = 1;
  new.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSADRAIN, &new) == -1)
    return (S_FAILURE);
  return (S_SUCCESS);
}

/*
** set term
** clean buffer
** set cursor invisible
*/
static void		interface_use_init(t_interface *interface)
{
  interface_set_term(&interface->term);
  tputs(interface->esc_seq.output[ESOUT_CURSOR_INV], 0, &the_putchar);
  memset(interface->read_buf.cmd.buf, 0, interface->read_buf.cmd.idx);
  memset(&interface->read_buf.completion, 0, sizeof(t_cmd_completion));
  interface->read_buf.cmd.idx = 0;
  interface->read_buf.cursor.x = 0;
  interface->read_buf.cursor.y = 0;
}

/*
** read input until there is a complete command
** for each input read get a list of token
** and print the line
** return S_FAILURE in case the shell shall quit
** return S_SUCCESS if nothing wrong
*/
static t_istatus	interface_get_cmd_line(t_interface *interface)
{
  t_istatus		state;

  while ((state = input_read(interface)) == S_FAILURE)
    interface_print(interface, B_TRUE);
  if (state == S_STOP)
    return (S_FAILURE);
  return (S_SUCCESS);
}

/*
** add new command to historic
** write new command to historic file
** if it is the same as the previous one nothing is done
*/
static void		interface_add_historic_cmd(t_historic *historic,
						   char *cmd,
						   t_interface *interface)
{
  t_var			*str;

  if (historic->fd == -1)
    historic->fd = open(HISTO_FILE_PATH HISTO_FILE_NAME,
			O_RDWR | O_APPEND | O_CREAT, 0644);
  if (!(str = the_find_env(interface->shell->var, VAR_PWD)))
    return ;
  if (!historic->cur || the_strcmp(historic->cur->name, str->value))
  {
    historic->cur = historic_get_dir(&historic->dir, str->value);
    if (historic->fd != -1)
    {
      the_putstr(historic->fd, HISTO_PATH_SCOPE);
      the_putstr(historic->fd, str->value);
      the_putstr(historic->fd, "\n");
    }
  }
  if (historic->cur && historic->fd != -1
      && (!historic->cur->cmd || the_strcmp(historic->cur->cmd->str, cmd)))
  {
    the_putstr(historic->fd, cmd);
    the_putstr(historic->fd, "\n");
  }
  if (historic->cur)
    historic_new_cmd(historic->cur, strdup(cmd));
}

/*
** set term
** get next command line in interface
** unset term
** return command line
** return NULL if something went wrong or EOF
*/
char const		*interface_use(t_interface *interface,
				       char * const env[])
{
  exec_no_args_functions(FUNCTIONS_PROMPT, interface->shell);
  if (!!tcgetattr(0, &interface->term))
  {
    dprintf(2, "%s\n", MSG_ERR ERR_TCGETATTR);
    return (NULL);
  }
  interface_use_init(interface);
  if (!!interface_get_position(interface, &interface->read_buf.prompt))
    return (NULL);
  interface_print(interface, B_TRUE);
  if (!!interface_get_cmd_line(interface))
    return (NULL);
  interface_print(interface, B_FALSE);
  the_putstr(1, "\n");
  if (!!tcsetattr(0, TCSANOW, &interface->term))
    dprintf(2, "%s\n", MSG_WRNG ERR_TCSETATTR);
  interface_add_historic_cmd(&interface->historic, interface->read_buf.cmd.buf,
			     interface);
  interface->historic.selected = NULL;
  tputs(interface->esc_seq.output[ESOUT_CURSOR_VIS], 0, &the_putchar);
  return (interface->read_buf.cmd.buf);
}
