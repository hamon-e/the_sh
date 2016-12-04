/*
** input_init_esc_seq.c for PSU_2015_42sh in sources/ncurses/input_management
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:24:30 2016 Nicolas Goudal
** Last update Thu Dec 01 11:01:13 2016
*/

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>
#include <term.h>
#include "interface/escape_sequence_response.h"
#include "interface/error_define.h"

static const t_esc_seq_input_dico	g_esc_seq_input_dico[] =
{
  {"kcuf1", ESIN_KEY_RIGHT, &input_right_arrow_response},
  {"kcub1", ESIN_KEY_LEFT, &input_left_arrow_response},
  {"kcuu1", ESIN_KEY_UP, &input_up_arrow_response},
  {"kcud1", ESIN_KEY_DOWN, &input_down_arrow_response},
  {"kdch1", ESIN_KEY_DELETE, &input_suppr_response},
  {"kbs", ESIN_KEY_BKSPACE, &input_delete_response},
  {"khome", ESIN_KEY_HOME, &input_home_response},
  {"kend", ESIN_KEY_END, &input_end_line_response},
  {NULL, 0, NULL}
};

static const t_esc_seq_output_dico	g_esc_seq_output_dico[] =
{
  {"sc", ESOUT_SAVE_CURSOR},
  {"rc", ESOUT_RESTORE_CURSOR},
  {"civis", ESOUT_CURSOR_INV},
  {"cnorm", ESOUT_CURSOR_VIS},
  {"cuf1", ESOUT_MCURSOR_RIGHT},
  {"cub1", ESOUT_MCURSOR_LEFT},
  {"cuf", ESOUT_MCURSOR_RIGHT_X},
  {"cub", ESOUT_MCURSOR_LEFT_X},
  {"cuu1", ESOUT_MCURSOR_UP},
  {"cud1", ESOUT_MCURSOR_DOWN},
  {"dl1", ESOUT_DELETE_LINE},
  {"cr", ESOUT_CARRIAGE_RETURN},
  {"ed", ESOUT_CLEAR_BELOW},
  {"smso", ESOUT_ENTER_STANDOUT},
  {"rmso", ESOUT_EXIT_STANDOUT},
  {"smul", ESOUT_ENTER_UNDERLINE},
  {"rmul", ESOUT_EXIT_UNDERLINE},
  {"u7", ESOUT_GET_POS},
  {NULL, 0}
};

static void	init_input_termcaps(t_esc_seq *esc_seq)
{
  int		i;
  char		*seq;

  i = 0;
  while (g_esc_seq_input_dico[i].seq)
  {
    if ((seq = tigetstr(g_esc_seq_input_dico[i].seq))
	&& seq != (char *)-1)
    {
      esc_seq[g_esc_seq_input_dico[i].id].seq = seq;
      esc_seq[g_esc_seq_input_dico[i].id].response
	= g_esc_seq_input_dico[i].response;
    }
    else
      printf(ERR_TCAPS, g_esc_seq_input_dico[i].seq);
    ++i;
  }
}

static void	init_output_termcaps(char **output)
{
  int		i;
  char		*seq;

  i = 0;
  while (g_esc_seq_output_dico[i].seq)
  {
    if ((seq = tigetstr(g_esc_seq_output_dico[i].seq))
	&& seq != (char *)-1)
      output[g_esc_seq_output_dico[i].id] = seq;
    else
      dprintf(2, ERR_TCAPS, g_esc_seq_output_dico[i].seq);
    ++i;
  }
}

static void			init_add_custom_esc_seq(t_esc_seq_tab *esc_seq)
{
  int				i;
  static t_esc_seq_input_dico	esc_seq_input[] =
  {
    {"\x1b\n\0", ESIN_KEY_ALT_ENTER, 0},
    {NULL, 0, 0}
  };

  i = 0;
  while (esc_seq_input[i].seq)
  {
    esc_seq->input[esc_seq_input[i].id].response = esc_seq_input[i].response;
    esc_seq->input[esc_seq_input[i].id].seq = esc_seq_input[i].seq;
    ++i;
  }
}

t_istatus	init_esc_seq(t_esc_seq_tab *esc_seq)
{
  char		*seq;

  if (setupterm(NULL, 1, NULL) == ERR
      || !(seq = tigetstr("smkx")) || seq == (char *)-1)
    return (S_FAILURE);
  the_putstr(1, seq);
  init_input_termcaps(esc_seq->input);
  init_add_custom_esc_seq(esc_seq);
  init_output_termcaps(esc_seq->output);
  return (S_SUCCESS);
}
