/*
** interface_print_completion.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:29:36 2016 Nicolas Goudal
** Last update Thu Dec 01 11:05:15 2016
*/

#include <term.h>
#include <unistd.h>
#include "interface/interface_private.h"

static void	print_a_completion(t_completion_list *completion,
				   int length_per_completion,
				   t_interface *interface)
{
  int		i;

  if (completion == interface->read_buf.completion.comp.selected)
    tputs(interface->esc_seq.output[ESOUT_ENTER_STANDOUT], 1, &the_putchar);
  the_putstr(1, completion->str);
  if (completion == interface->read_buf.completion.comp.selected)
    tputs(interface->esc_seq.output[ESOUT_EXIT_STANDOUT], 0, &the_putchar);
  i = length_per_completion - completion->length;
  interface->read_buf.len += length_per_completion;
  while (i >= 0)
  {
    write(1, " ", 1);
    --i;
  }
}

void			interface_print_completion(t_interface *interface)
{
  t_completion_list	*list;
  t_completion_buf	*buf;
  int			i;

  if (!interface->read_buf.completion.comp.list)
    return ;
  interface_print_new_line(interface);
  buf = &interface->read_buf.completion.comp;
  list = buf->list;
  i = 0;
  while (list)
  {
    if (i == buf->nbr_per_line)
    {
      interface_print_new_line(interface);
      i = 0;
    }
    print_a_completion(list, buf->length_per_completion, interface);
    list = list->next;
    ++i;
  }
}
