/*
** interface_complete_idx_finder.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:22:23 2016 Nicolas Goudal
** Last update Sat Dec 03 12:56:46 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "the_parser/rules.h"
#include "interface/interface_private.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

t_completion_list	*interface_complete_idx_finder(t_interface *interface,
						       t_graph *graph)
{
  t_complete_command	command;

  if (!graph || !graph->detail || the_strcmp(graph->detail->rule, "lexer"))
    return (NULL);
  command.name = NULL;
  command.actual = NULL;
  command.before = NULL;
  interface->read_buf.completion.comp.idx = 0;
  interface->read_buf.completion.comp.len = 0;
  graph_search(interface, graph->detail->detail, &command);
  if (command.before && !command.actual)
  {
    command.actual = command.before;
    command.before = NULL;
  }
  the_free(1, FREE_GRAPH, graph);
  return (complete_on_event(interface->shell, &command));
}
