/*
** interface_print_reserved.c for PSU_2015_42sh in sources/ncurses/interface_print
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:30:21 2016 Nicolas Goudal
** Last update Sat Dec 03 12:50:02 2016 Benoit Hamon
*/

#include <term.h>
#include <unistd.h>
#include "interface/interface_print.h"
#include "interface/interface_private.h"

void			interface_print_combiner(t_graph *graph,
						 t_interface *interface,
						 char const *color,
						 char const **prev_addr)
{
  int			i;

  interface_print_token(graph, interface, color, prev_addr);
  if (interface->reserved.is_reserved)
  {
    interface_print_new_line(interface);
    i = 0;
    if (interface->read_buf.prompt.x)
    {
      tputs(tparm(interface->esc_seq.output[ESOUT_MCURSOR_RIGHT_X],
		  interface->read_buf.prompt.x), 0, &the_putchar);
      interface->read_buf.len += interface->read_buf.prompt.x;
    }
    while (i < interface->reserved.indent)
    {
      write(1, "  ", 2);
      interface->read_buf.len += 2;
      ++i;
    }
  }
}

void			interface_print_reserved(t_graph *graph,
						 t_interface *interface,
						 char const *color,
						 char const **prev_addr)
{
  interface->reserved.is_reserved = B_TRUE;
  ++interface->reserved.indent;
  interface_print_token(graph, interface, color, prev_addr);
}

void			interface_print_reserved_no(t_graph *graph,
						    t_interface *interface,
						    char const *color,
						    char const **prev_addr)
{
  interface->reserved.is_reserved = B_TRUE;
  --interface->reserved.indent;
  interface_print_token(graph, interface, color, prev_addr);
}

void			interface_print_reserved_end(t_graph *graph,
						     t_interface *interface,
						     char const *color,
						     char const **prev_addr)
{
  if (interface->reserved.is_reserved && interface->reserved.indent > 0)
    --interface->reserved.indent;
  if (interface->reserved.indent <= 0)
    interface->reserved.is_reserved = B_FALSE;
  interface_print_token(graph, interface, color, prev_addr);
}
