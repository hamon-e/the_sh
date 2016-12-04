/*
** interface_print.h for  in /home/lin_p/PSU_2015_42sh/include/interface
**
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
**
** Started on  Sat Jun  4 05:35:17 2016 Lin Patrick
** Last update Thu Dec 01 15:39:32 2016
*/

#ifndef INTERFACE_PRINT_H_
# define INTERFACE_PRINT_H_

# include "interface_private.h"
# include "the_parser/parser.h"

typedef struct		s_token_dico
{
  char			*rule;
  void			(*func)();
  int			color;
  int			detail;
}			t_token_dico;

void			interface_print(t_interface *interface,
					t_bool print_cur);
void			interface_print_completion(t_interface *interface);
void			interface_print_command_line(t_interface *interface,
						     t_graph *graph);
void			interface_print_check_token(t_graph *graph,
						    t_interface *interface,
						    char const **prev_addr);
void			interface_print_combiner(t_graph *graph,
						 t_interface *interface,
						 char const *color,
						 char const **prev_addr);
void			interface_print_reserved(t_graph *graph,
						 t_interface *interface,
						 char const *color,
						 char const **prev_addr);
void			interface_print_reserved_no(t_graph *graph,
						    t_interface *interface,
						    char const *color,
						    char const **prev_addr);
void			interface_print_reserved_end(t_graph *graph,
						     t_interface *interface,
						     char const *color,
						     char const **prev_addr);
void			interface_print_str(char const *str,
					    int size,
					    t_interface *interface);
void			interface_print_token(t_graph *graph,
					      t_interface *interface,
					      char const *color,
					      char const **prev_addr);
void			interface_print_cmd(t_graph *graph,
					    t_interface *interface,
					    char *color,
					    char const **prev_addr);
void			interface_print_redir(t_graph *graph,
					      t_interface *interface,
					      char const *color,
					      char const **prev_addr);
void			interface_print_substitution(t_graph *graph,
						     t_interface *interface,
						     char const *color,
						     char const **prev_addr);
void			interface_print_spe(t_graph *graph,
					    t_interface *interface,
					    char const *color,
					    char const **prev_addr);
void			interface_print_comp(t_graph *graph,
					     t_interface *interface,
					     char const *color,
					     char const **prev_addr);
#endif /* INTERFACE_PRINT_H_ */
