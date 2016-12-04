/*
** set_private.h for PSU_2015_42sh in include/builtins
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Jun 05 16:09:20 2016 Benoit Hamon
** Last update Sun Jun 05 16:10:02 2016 Benoit Hamon
*/

#ifndef SET_PRIVATE_H_
# define SET_PRIVATE_H_

# include "set.h"

typedef enum		e_opt_bit
{
  OPT_LOCAL = 1,
  OPT_GLOBAL = 2,
  OPT_EXPORT = 4,
  OPT_ERASE = 8,
  OPT_QUERY = 16,
  OPT_NAMES = 32
}			t_opt_bit;

typedef struct		s_set_func
{
  int			type;
  t_status		(*f)();
}			t_set_func;

/*
** Set tools
*/
void			*set_get_scope(t_var_list *var,
				       char const *str,
				       int opt);
char			*set_get_name(char const *str, int *n);
void			the_push_at_index(t_var_ctrl *scope, t_var *elem);
t_status		delete_at_index(t_var_ctrl *scope, int const index);

/*
** Set options
*/
t_status		set_new(t_opt const *opt, t_shell *shell);

#endif /* end of include guard: SET_PRIVATE_H_ */
