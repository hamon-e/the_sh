/*
** find.h for PSU_2015_42sh in sources/find
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 23:44:01 2016 Benoit Hamon
** Last update Fri Jun 03 15:07:49 2016 Benoit Hamon
*/

#ifndef FIND_H_
# define FIND_H_

typedef enum		e_cmd_type
{
  CMD_DBINARY = 1,
  CMD_PBINARY,
  CMD_BUILTIN,
  CMD_FUNCTION
}			t_cmd_type;

bool		check_access(char const *str, bool verbose);

t_cmd_type	the_access(t_shell *shell,
			   t_var *path,
			   char const *cmd,
			   bool verbose);

t_var		*the_find_env(t_var_list *var, char const *name);
char		*the_find_path(t_var *path, char const *cmd);

char		*the_concatchar(char const *dir, char const *file, char c);

#endif /* end of include guard: FIND_H_ */
