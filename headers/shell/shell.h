/*
** shell.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 17:40:01 2016 Benoit Hamon
** Last update Thu Dec 01 20:04:02 2016 Benoit Hamon
*/

#ifndef SHELL_H_
# define SHELL_H_

# include "complete/complete.h"

typedef struct		s_var
{
  char			*value;
  int			index;
  struct s_var		*next;
}			t_var;

typedef struct		s_var_ctrl
{
  t_var			*list;
  int			nbr;
}			t_var_ctrl;

typedef struct		s_var_list
{
  char const		*name;
  t_var_ctrl		*local;
  t_var_ctrl		*global;
  t_var_ctrl		*export;
  struct s_var_list	*next;
}			t_var_list;

typedef struct		s_func_list
{
  char const		*name;
  char const		*cmd;
  struct s_func_list	*next;
}			t_func_list;

typedef struct s_complete	t_complete;

typedef struct		s_shell
{
  void			*grammar;
  bool			carry;
  int			exit;
  int			stack;
  char			**env;
  t_var_list		*var;
  t_func_list		*func;
  t_complete		*complete;
}			t_shell;

#endif /* end of include guard: SHELL_H_ */
