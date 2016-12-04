/*
** interface_print_token.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:30:58 2016 Nicolas Goudal
** Last update Thu Dec 01 11:06:19 2016
*/

#include <stdbool.h>
#include <term.h>
#include <unistd.h>
#include "the_parser/rules.h"
#include "interface/interface_private.h"
#include "interface/interface_print.h"
#include "interface/color.h"

static void	interface_print_str_part(char const *str,
					 int size,
					 t_interface *interface)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str && str[i + j] && (i + j) < size)
  {
    if (str[i + j] == '\n')
    {
      write(1, str + i, j);
      interface->read_buf.len += j;
      interface_print_new_line(interface);
      tputs(tparm(interface->esc_seq.output[ESOUT_MCURSOR_RIGHT_X],
		  interface->read_buf.prompt.x),
	    0, &the_putchar);
      interface->read_buf.len += interface->read_buf.prompt.x;
      i += j + 1;
      j = -1;
    }
    ++j;
  }
  if (j)
    write(1, str + i, j);
  interface->read_buf.len += j;
}

static void		interface_print_command(char const *str,
						int size,
						t_interface *interface)
{
  char const		*cur_pos;
  int			i;

  if (!size || !str)
    return ;
  cur_pos = interface->read_buf.cur_line + interface->read_buf.cur_size
    + interface->read_buf.cursor.x;
  if (!interface->print_cursor || (cur_pos < str || cur_pos >= str + size))
    interface_print_str_part(str, size, interface);
  else
  {
    i = cur_pos - str;
    interface_print_str_part(str, i, interface);
    tputs(interface->esc_seq.output[ESOUT_ENTER_STANDOUT], 0, &the_putchar);
    write(1, str + i, 1);
    ++interface->read_buf.len;
    tputs(interface->esc_seq.output[ESOUT_EXIT_STANDOUT], 0, &the_putchar);
    if (size - i > 0)
      interface_print_str_part(str + i + 1, size - i - 1, interface);
  }
}

static void		interface_print_historic(char const *str,
						 int size,
						 t_interface *interface,
						 t_cmd_completion *completion)
{
  int			move;
  int			i;

  if (!interface->read_buf.completion.aff
      || (str > (completion->aff + completion->aff_len))
      || (str + size) < (completion->aff))
    interface_print_command(str, size, interface);
  else
  {
    if ((move = completion->aff - str) < 0)
      move = 0;
    interface_print_command(str, move, interface);
    tputs(interface->esc_seq.output[ESOUT_ENTER_UNDERLINE], 0, &the_putchar);
    if ((i = size - move)
	&& str + i + move > (completion->aff + completion->aff_len))
      i -= ((str + i + move) - (completion->aff + completion->aff_len));
    interface_print_command(str + move, i, interface);
    tputs(interface->esc_seq.output[ESOUT_EXIT_UNDERLINE], 0, &the_putchar);
    if (move + i < size)
      interface_print_command(str + move + i, size - move - i, interface);
  }
}

void			interface_print_str(char const *str,
					    int size,
					    t_interface *interface)
{
  t_completion_buf	*comp;

  if (!str)
    return ;
  comp = &interface->read_buf.completion.comp;
  if (comp->list && comp->selected
      && str >= (interface->read_buf.cmd.buf + comp->idx)
      && str < (interface->read_buf.cmd.buf + comp->idx + comp->len))
    interface_print_command(comp->selected->str, comp->selected->length,
			    interface);
  else if (!interface->read_buf.completion.str)
    interface_print_command(str, size, interface);
  else
    interface_print_historic(str, size, interface,
			     &interface->read_buf.completion);
}

void			interface_print_token(t_graph *graph,
					      t_interface *interface,
					      char const *color,
					      char const **prev_addr)
{
  if (!graph)
    return ;
  if (prev_addr && graph->str > *prev_addr)
    interface_print_str(*prev_addr, graph->str - *prev_addr, interface);
  the_putstr(1, color);
  interface_print_str(graph->str, graph->size, interface);
  the_putstr(1, interface->color[DEFAULT_COLOR].fgd);
  if (prev_addr)
    *prev_addr = graph->str + graph->size;
}
