/*
** echo.h for PSU_2015_42sh in include/builtins
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:47:49 2016 Nicolas Goudal
** Last update Sun Jun 05 20:48:00 2016 Nicolas Goudal
*/

#ifndef ECHO_H_
# define ECHO_H_

typedef enum		e_opt_bit
{
  OPT_NEWLINE = 1,
  OPT_NO_SPACES = 2,
}			t_opt_bit;

typedef struct		s_echo_dico
{
  char			c;
  t_opt_bit		type;
}			t_echo_dico;

#endif /* end of include guard: ECHO_H_ */
