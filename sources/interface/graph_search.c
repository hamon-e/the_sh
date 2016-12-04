/*
** graph_search.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:19:53 2016 Nicolas Goudal
** Last update Thu Dec 01 10:57:07 2016
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "the_parser/rules.h"
#include "interface/interface_private.h"
#include "complete/complete_private.h"
#include "complete/complete.h"

static bool		is_within_addr_range(char const *addr,
					     char const *range_min,
					     char const *range_max)
{
  if (addr >= range_min && addr < range_max)
    return (true);
  return (false);
}

static t_istatus	graph_search_even_deeper(t_interface *interface,
						 t_graph *graph,
						 char *addr,
						 t_complete_command *command)
{
  if (!graph)
    return (S_FAILURE);
  while (graph)
  {
    if (is_within_addr_range(addr, graph->str, graph->str + graph->size))
    {
      interface->read_buf.completion.comp.idx
	= graph->str - interface->read_buf.cmd.buf;
      interface->read_buf.completion.comp.len = graph->size;
      command->actual = strndup(graph->str, graph->size);
      return (S_SUCCESS);
    }
    else
    {
      if (command->before)
	free(command->before);
      command->before = strndup(graph->str, graph->size);
    }
    graph = graph->next;
  }
  return (S_FAILURE);
}

static t_istatus	graph_search_deeper(t_interface *interface,
					    t_graph *graph,
					    char *addr,
					    t_complete_command *command)
{
  if (!graph)
    return (S_SUCCESS);
  if (command->name)
    free(command->name);
  command->name = strndup(graph->str, graph->size);
  if (!is_within_addr_range(addr, graph->str, graph->str + graph->size))
    return (graph_search_even_deeper(interface, graph->next, addr, command));
  return (S_SUCCESS);
}

static t_bool		graph_search_cmd(t_interface *interface,
					 t_graph *graph,
					 t_complete_command *command)
{
  interface->read_buf.completion.comp.idx
    = graph->str - interface->read_buf.cmd.buf;
  interface->read_buf.completion.comp.len = graph->size;
  return (B_TRUE);
}

void			graph_search(t_interface *interface,
				     t_graph *graph,
				     t_complete_command *command)
{
  char			*addr;
  t_bool		status;

  addr = interface->read_buf.cmd.buf
    + interface->read_buf.cmd.idx + interface->read_buf.cursor.x;
  status = B_FALSE;
  while (graph)
  {
    if (is_within_addr_range(addr, graph->str, graph->str + graph->size))
      status = graph_search_cmd(interface, graph, command);
    else
    {
      interface->read_buf.completion.comp.idx = interface->read_buf.cmd.idx
	+ interface->read_buf.cursor.x;
      interface->read_buf.completion.comp.len = 1;
    }
    if ((!the_strcmp(graph->rule, PARSER_CMD)
	 && !graph_search_deeper(interface, graph->detail, addr, command))
	|| status)
      return ;
    graph = graph->next;
  }
}
