/*
** functions.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 01:43:50 2016 Benoit Hamon
** Last update Sun Jun 05 13:33:53 2016 Benoit Hamon
*/

#ifndef FUNCTIONS_H_
# define FUNCTIONS_H_

#define MAX_STACK	1000

bool			is_function(t_shell *shell, char const *cmd);
bool			exec_functions(int argc,
				       char const **argv,
				       t_shell *shell);
bool			exec_no_args_functions(char const *name,
					       t_shell *shell);

#endif /* end of include guard: FUNCTIONS_H_ */
