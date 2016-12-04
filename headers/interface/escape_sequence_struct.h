/*
** escape_sequence_struct.h for  in /home/lin_p/test/42sh/include
** 
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
** 
** Started on  Mon May 23 19:18:22 2016 Lin Patrick
** Last update Sat Jun  4 19:49:03 2016 Lin Patrick
*/

#ifndef ESCAPE_SEQUENCE_STRUCT_H_
# define ESCAPE_SEQUENCE_STRUCT_H_

# include "interface_status.h"

typedef enum			e_esc_seq_input_id
  {
    ESIN_KEY_UP,
    ESIN_KEY_DOWN,
    ESIN_KEY_RIGHT,
    ESIN_KEY_LEFT,
    ESIN_KEY_HOME,
    ESIN_KEY_END,
    ESIN_KEY_BKSPACE,
    ESIN_KEY_DELETE,
    ESIN_KEY_PAGE_UP,
    ESIN_KEY_PAGE_DOWN,
    ESIN_KEY_ALT_ENTER,
    ESIN_END
  }				t_esc_seq_input_id;

typedef enum			e_esc_seq_output_id
  {
    ESOUT_SAVE_CURSOR,
    ESOUT_RESTORE_CURSOR,
    ESOUT_CURSOR_INV,
    ESOUT_CURSOR_VIS,
    ESOUT_MCURSOR_RIGHT,
    ESOUT_MCURSOR_RIGHT_X,
    ESOUT_MCURSOR_LEFT,
    ESOUT_MCURSOR_LEFT_X,
    ESOUT_MCURSOR_UP,
    ESOUT_MCURSOR_DOWN,
    ESOUT_DELETE_LINE,
    ESOUT_CARRIAGE_RETURN,
    ESOUT_CLEAR_BELOW,
    ESOUT_ENTER_STANDOUT,
    ESOUT_EXIT_STANDOUT,
    ESOUT_ENTER_UNDERLINE,
    ESOUT_EXIT_UNDERLINE,
    ESOUT_GET_POS,
    ESOUT_END
  }				t_esc_seq_output_id;

typedef struct			s_esc_seq_input_dico
{
  char				*seq;
  t_esc_seq_input_id		id;
  t_istatus			(*response)();
}				t_esc_seq_input_dico;

typedef struct			s_esc_seq_output_dico
{
  char				*seq;
  t_esc_seq_output_id		id;
}				t_esc_seq_output_dico;

typedef struct			s_esc_seq
{
  char				*seq;
  t_istatus			(*response)();
}				t_esc_seq;

typedef struct			s_esc_seq_tab
{
  t_esc_seq			input[ESIN_END];
  char				*output[ESOUT_END];
  char				color;
}				t_esc_seq_tab;

int			init_esc_seq(t_esc_seq_tab *esc_seq);

#endif /* ESCAPE_SEQUENCE_STRUCT_H_ */
