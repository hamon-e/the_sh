/*
** exec.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 10:07:23 2016 Benoit Hamon
** Last update Thu Dec 01 20:09:40 2016 Benoit Hamon
*/

#ifndef EXEC_H_
# define EXEC_H_

void		exec(t_shell *shell, t_graph *graph);
void		exec_file(t_shell *shell,
			  char const *file);
bool		exec_pbinary(int argc,
			     char const **argv,
			     t_shell *shell);

#endif /* end of include guard: EXEC_H_ */
