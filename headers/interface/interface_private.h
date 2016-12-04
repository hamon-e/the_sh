/*
** interface.h for  in /home/lin_p/test/42sh/include
**
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
**
** Started on  Sat Apr 30 16:03:23 2016 Lin Patrick
** Last update Thu Dec 01 20:53:03 2016 Benoit Hamon
*/

#ifndef INTERFACE_PRIVATE_H_
# define INTERFACE_PRIVATE_H_

# include <stddef.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include "interface_status.h"
# include "escape_sequence_struct.h"
# include "historic_private.h"
# include "interface_complete.h"
# include "color.h"
# include "the_parser/parser.h"
# include "shell/shell.h"

# define I_BUF_SIZE		255
# define I_INP_SIZE		80

# define PWD_VAR		"PWD="

# define MAX_ASCII_VALUE	177

typedef enum			e_bool
  {
    B_FALSE,
    B_TRUE
  }				t_bool;

typedef enum			e_startcmp_value
  {
    CMP_CORRESPOND,
    CMP_SEEMS,
    CMP_DIFFERENT
  }				t_startcmp_value;

typedef struct			s_special_char_func
{
  int				spe_char;
  t_istatus			(*func)();
}				t_special_char_func;

typedef struct			s_buffer
{
  char				*buf;
  int				idx;
  int				size;
}				t_buffer;

typedef struct			s_cursor
{
  int				x;
  int				y;
}				t_cursor;

typedef t_cursor		t_position;

typedef struct			s_read_buf
{
  t_buffer			cmd;
  t_cmd_completion		completion;
  t_buffer			input;
  t_cursor			cursor;
  int				len;
  t_position			prompt;
  char const			*cur_line;
  int				cur_size;
}				t_read_buf;

typedef struct			s_reserved
{
  t_bool			is_reserved;
  int				indent;
}				t_reserved;

typedef struct			s_interface
{
  t_read_buf			read_buf;
  t_bool			print_cursor;
  t_reserved			reserved;
  t_esc_seq_tab			esc_seq;
  t_historic			historic;
  void				*lexer;
  t_color_set			color[END_COLOR];
  t_shell			*shell;
  struct termios		term;
  struct winsize		win_size;
}				t_interface;

void			interface_init_color(t_interface *interface);
void			interface_init_completion(t_interface *interface,
						  t_graph *graph);
void			graph_search(t_interface *interface,
				     t_graph *graph,
				     t_complete_command *command);
t_completion_list	*interface_complete_idx_finder(t_interface *interface,
						       t_graph *graph);
void			interface_check_historic(t_interface *interface);
t_istatus		input_read(t_interface *interface);
t_istatus		interface_get_position(t_interface *interface,
					       t_position *pos);
void			interface_print_command_line(t_interface *interface,
						     t_graph *graph);
void			interface_print(t_interface *interface,
					t_bool print_cur);
void			interface_print_new_line(t_interface *interface);

/*
** TO DELETE
*/
void				*free_graph(t_graph *graph);
int				the_putchar(int c);
void				the_putstr(int const fd,
					   char const *str);
int				the_strlen(char const *str);
int				the_strcmp(char const *str1,
					   char const *str2);
void				the_pushback(void **list, void *elem, int n);
void				the_pushfront(void **list, void *elem, int n);
void				the_pushback2(void **list, void *elem,
					      size_t next, size_t prev);
void				the_pushfront2(void **list, void *elem,
					       size_t next, size_t prev);

#endif /* !INTERFACE_PRIVATE_H_ */
