/*
** interface_init.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:21:58 2016 Nicolas Goudal
** Last update Thu Dec 01 20:54:43 2016 Benoit Hamon
*/

#include <sys/ioctl.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <term.h>
#include "interface/interface.h"
#include "interface/error_define.h"

t_interface		g_interface;

static void		interface_resize_signal_handler(int signum)
{
  signal(SIGWINCH, &interface_resize_signal_handler);
  if (signum != SIGWINCH)
    return ;
  ioctl(0, TIOCGWINSZ, &g_interface.win_size);
  interface_print(&g_interface, B_TRUE);
}

static t_istatus	interface_init_read_buf(void)
{
  if (!(g_interface.read_buf.cmd.buf
	= malloc(sizeof(char) * (I_BUF_SIZE + 1))))
    return (S_FAILURE);
  g_interface.read_buf.cmd.idx = 0;
  g_interface.read_buf.cmd.size = I_BUF_SIZE;
  memset(g_interface.read_buf.cmd.buf, 0, sizeof(char) * (I_BUF_SIZE + 1));
  return (S_SUCCESS);
}

t_interface		*interface_init(void *lexer, t_shell *shell)
{
  memset(&g_interface, 0, sizeof(t_interface));
  historic_init(&g_interface.historic);
  g_interface.lexer = lexer;
  if (!!ioctl(0, TIOCGWINSZ, &g_interface.win_size))
  {
    dprintf(2, "%s\n", ERR_IOCTL MSG_WHILE ERR_IOCTL_WSZ);
    return (NULL);
  }
  if (tgetent(NULL, "xterm") == ERR
      || !!init_esc_seq(&g_interface.esc_seq)
      || !!interface_init_read_buf())
  {
    dprintf(2, "%s\n", MSG_ERR ERR_ITF_INIT);
    return (NULL);
  }
  interface_init_color(&g_interface);
  if (signal(SIGWINCH, &interface_resize_signal_handler) == SIG_ERR)
    dprintf(2, "%s\n", MSG_WRNG ERR_SIGWINCH);
  g_interface.shell = shell;
  return (&g_interface);
}
