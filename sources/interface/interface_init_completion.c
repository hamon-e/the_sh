/*
** interface_init_completion.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:21:52 2016 Nicolas Goudal
** Last update Thu Dec 01 11:00:18 2016
*/

#include "interface/interface_complete.h"
#include "interface/interface_private.h"

/*
** count 'list' length
** thus set completion nbr of elem
** set length of each completion
** set number of completion per line
*/
static void	interface_init_spacement(t_completion_buf *completion,
					 t_completion_list *list,
					 int cols)
{
  int		count;
  int		length;

  count = 0;
  length = 0;
  while (list)
  {
    if (length < list->length)
      length = list->length;
    ++count;
    list = list->next;
  }
  completion->length_per_completion = length + 2;
  completion->nbr_per_line = (cols
			      / completion->length_per_completion) / 2;
  completion->nbr_of_elem = count;
}

/*
** set the number of elem to print
** in case there is too much elements
** only the 'INIT_MAX_ROW' first row shall be displayed initally
*/
static void	interface_set_completion_start(t_completion_buf *completion)
{
  if (completion->nbr_of_elem > completion->nbr_per_line * INIT_MAX_ROW)
    completion->nbr_to_print = completion->nbr_per_line * INIT_MAX_ROW;
  else
    completion->nbr_to_print = completion->nbr_of_elem;
  completion->start = completion->list;
}

/*
** TEST
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
t_completion_list	*interface_test_completion()
{
  DIR			*dirp;
  struct dirent		*dir;
  t_completion_list	*list;
  t_completion_list	*new;

  dirp = opendir(".");
  list = NULL;
  while ((dir = readdir(dirp)))
  {
    if (!(new = malloc(sizeof(t_completion_list))))
      return (NULL);
    new->str = strdup(dir->d_name);
    new->desc = NULL;
    new->length = strlen(new->str);
    new->next = NULL;
    the_pushback((void **)&list, new, offsetof(t_completion_list, next));
  }
  return (list);
}

/*
** create a list of completion
** init postion value
*/
void		interface_init_completion(t_interface *interface,
					  t_graph *graph)
{
  if ((interface->read_buf.completion.comp.list
       = interface_complete_idx_finder(interface, graph)))
    interface->read_buf.completion.type = TAB_COMPL;
  else
    return ;
  interface->read_buf.completion.comp.selected = NULL;
  interface->read_buf.completion.comp.selected
    = interface->read_buf.completion.comp.list;
  interface_init_spacement(&interface->read_buf.completion.comp,
			   interface->read_buf.completion.comp.list,
			   interface->win_size.ws_col);
  interface_set_completion_start(&interface->read_buf.completion.comp);
}
