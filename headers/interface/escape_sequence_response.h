/*
** escape_sequence.h for  in /home/lin_p/test/42sh/include
** 
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
** 
** Started on  Mon May 23 16:38:31 2016 Lin Patrick
** Last update Sat Jun  4 20:34:00 2016 Lin Patrick
*/

#ifndef ESCAPE_SEQUENCE_H_
# define ESCAPE_SEQUENCE_H_

# include "escape_sequence_struct.h"
# include "interface.h"

t_istatus	input_right_arrow_response(t_interface *interface);
t_istatus	input_left_arrow_response(t_interface *interface);
t_istatus	input_down_arrow_response(t_interface *interface);
t_istatus	input_up_arrow_response(t_interface *interface);
t_istatus	input_delete_response(t_interface *interface);
t_istatus	input_suppr_response(t_interface *interface);
t_istatus	input_home_response(t_interface *interface);
t_istatus	input_end_line_response(t_interface *interface);
t_istatus	input_completion_response(t_interface *interface);

#endif /* !ESCAPE_SEQUENCE_H_ */
