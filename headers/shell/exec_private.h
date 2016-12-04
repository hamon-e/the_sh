/*
** exec_private.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 13:57:28 2016 Benoit Hamon
** Last update Sun Jun 05 23:39:42 2016 Benoit Hamon
*/

#ifndef EXEC_PRIVATE_H_
# define EXEC_PRIVATE_H_

# include "exec.h"

# define TMP_FILE	"./files/.tmp"

typedef struct		s_rule_func
{
  char const		*rule;
  void			(*f)();
}			t_rule_func;

typedef struct		s_exec_redir_func
{
  t_redir_type		type;
  bool			(*f)();
}			t_exec_redir_func;

typedef struct		s_exec_func
{
  t_cmd_type		type;
  bool			(*f)();
}			t_exec_func;

typedef struct		s_signal
{
  int			nbr;
  char const		*name;
  char const		*msg;
}			t_signal;

bool		exec_reset_fd(int *fd_save);
bool		exec_redir(t_redir_list *redir, int *fd_save);
void		the_pipe(t_shell *shell, t_graph *graph);
void		print_signal(char const *cmd, int status);

void		exec_combiners();
void		exec_semicolon_tcsh();
void		exec_or_tcsh();
void		exec_and_tcsh();

void		exec_if();
void		exec_switch();
void		exec_function();
void		exec_while();

void		exec_or();
void		exec_and();
void		exec_pipe();
void		exec_bgnd();
void		exec_cmd();

#endif /* end of include guard: EXEC_PRIVATE_H_ */
