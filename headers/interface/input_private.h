/*
** input_private.h for  in /home/lin_p/PSU_2015_42sh/include
** 
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
** 
** Started on  Wed Jun  1 21:28:58 2016 Lin Patrick
** Last update Sun Jun  5 11:37:56 2016 Lin Patrick
*/

#ifndef INPUT_PRIVATE_H_
# define INPUT_PRIVATE_H_

# include <termios.h>
# include "interface_private.h"

typedef t_istatus	(*t_input_handler)(t_interface *interface,
					   char c,
					   t_istatus *status,
					   struct termios *term);

t_istatus		increase_buffer_size(t_buffer *buf,
					     int inc_size,
					     int min_size);
t_istatus		input_move_completion(t_interface *interface);
t_istatus		input_move_line_completion(t_interface *interface);
t_istatus		input_is_special_char(t_interface *interface,
					      char c,
					      t_istatus *status,
					      struct termios *term);

t_istatus		input_is_esc_seq(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term);
t_istatus		input_is_cmd_end(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term);
t_istatus		input_cat_buffer(t_interface *interface,
					 char c,
					 t_istatus *status,
					 struct termios *term);

#endif /* !INPUT_PRIVATE_H_ */
