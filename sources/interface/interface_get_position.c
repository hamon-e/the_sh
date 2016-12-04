/*
** interface_get_position.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:22:04 2016 Nicolas Goudal
** Last update Thu Dec 01 10:59:54 2016
*/

#include <unistd.h>
#include <term.h>
#include "interface/interface_private.h"

static t_istatus	interface_empty_input(t_interface *interface,
					      int bytes_left)
{
  t_istatus	status;
  int		i;

  i = 0;
  while (i < bytes_left
	 && (status = input_read(interface)) != S_SUCCESS)
  {
    if (status == S_STOP)
      return (status);
    ++i;
  }
  return (S_SUCCESS);
}

static t_istatus	interface_read_position(t_interface *interface,
						t_position *pos)
{
  char		c;

  pos->x = 0;
  pos->y = 0;
  if (!interface->esc_seq.output[ESOUT_GET_POS]
      || interface->esc_seq.output[ESOUT_GET_POS] == (char *)-1)
    return (S_SUCCESS);
  tputs(interface->esc_seq.output[ESOUT_GET_POS], 1, &the_putchar);
  read(1, &c, 1);
  read(1, &c, 1);
  while (read(1, &c, 1) > 0 && c >= '0' && c <= '9')
    pos->y = pos->y * 10 + c - '0';
  while (read(1, &c, 1) > 0 && c >= '0' && c <= '9')
    pos->x = pos->x * 10 + c - '0';
  --pos->x;
  --pos->y;
  return (S_SUCCESS);
}

t_istatus	interface_get_position(t_interface *interface,
				       t_position *pos)
{
  int		bytes_left;

  if (!!ioctl(0, FIONREAD, &bytes_left)
      || !!interface_empty_input(interface, bytes_left))
    return (S_FAILURE);
  if (!!interface_read_position(interface, pos))
    return (S_FAILURE);
  return (S_SUCCESS);
}
