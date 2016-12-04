/*
** set.h for PSU_2015_42sh in include/builtins
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Jun 05 16:08:31 2016 Benoit Hamon
** Last update Mon Jun  6 01:15:42 2016 
*/

#ifndef SET_H_
# define SET_H_

# define VAR_STATUS	"status"
# define VAR_ARGS	"argv"

char			**recreate_env(t_var_list *var_list);
t_status		find_env_var(char **env,
				     char const *name,
				     int *n);
void			free_var_list(t_var *list);

t_status		add_tab_var_local(t_shell *shell,
					  char const *name,
					  char const **value);
t_status		add_int_var_global(t_shell *shell,
					   char const *name,
					   int value);
t_status		add_string_var_export(t_shell *shell,
					      char const *name,
					      char const *value);
t_status		add_string_var_local(t_shell *shell,
					     char const *name,
					     char const *value);
void			free_all_local_var(t_shell *shell);

#endif /* end of include guard: SET_H_ */
