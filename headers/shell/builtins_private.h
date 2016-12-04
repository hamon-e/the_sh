/*
** builtins_private.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 10:10:44 2016 Benoit Hamon
** Last update Sun Jun 05 23:37:54 2016 Nicolas Goudal
*/

#ifndef BUILTINS_PRIVATE_H_
# define BUILTINS_PRIVATE_H_

typedef struct		s_builtin_func
{
  char const		*cmd;
  bool			(*f)();
}			t_builtin_func;

bool			test(int argc, char const* argv[]);
bool			the_set(int argc,
				char const *argv[],
				t_shell *shell);
bool			the_exit(int argc,
				 char const *argv[],
				 t_shell *shell);
bool			command(int argc,
				char const *argv[],
				t_shell *shell);
bool			the_echo(int argc,
				 char const *argv[]);
bool			the_cd(int argc,
			       char const *argv[],
			       t_shell *shell);
bool			the_complete(int argc,
				     char const *argv[],
				     t_shell *shell);
bool			the_split(int argc,
				  char const *argv[]);
bool			the_set_color(int argc,
				      char const *argv[]);

#endif /* end of include guard: BUILTINS_PRIVATE_H_ */
