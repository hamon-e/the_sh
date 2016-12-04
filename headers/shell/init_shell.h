/*
** init_shell.h for PSU_2015_42sh in include/shell
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Jun 04 20:31:44 2016 Benoit Hamon
** Last update Thu Dec 01 20:41:32 2016 Benoit Hamon
*/

#ifndef INIT_SHELL_H_
# define INIT_SHELL_H_

typedef struct		s_opt_shell
{
  char			*grammar;
  char			*command;
  int			debug;
}			t_opt_shell;

typedef enum		e_opt_bit
{
  OPT_GRAMMAR = 1,
  OPT_COMMAND = 2,
  OPT_EXECUTE = 4,
  OPT_DEBUG = 8
}			t_opt_bit;

bool			init_shell(t_shell *shell,
				   char const *envp[],
				   int opt);
int			launch_shell(t_shell *shell,
				     t_opt *opt);
void			shell_loop(t_shell *shell,
				   t_opt *opt,
				   char const *str);

#endif /* end of include guard: INIT_SHELL_H_ */
