/*
** build_cmd.h for PSU_2015_42sh in sources/generic
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu May 26 22:40:43 2016 Benoit Hamon
** Last update Sun Jun 05 19:29:09 2016 Nicolas Goudal
*/

#ifndef BUILD_CMD_H_
# define BUILD_CMD_H_

# define ESCAPE_SEQUENCE	"abtnvfr"

typedef enum		e_redir_type
{
  REDIR_LEFT = 1,
  REDIR_RIGHT,
  REDIR_DOUBLE_LEFT,
  REDIR_DOUBLE_RIGHT
}			t_redir_type;

typedef struct		s_arg_list
{
  char			*str;
  struct s_arg_list	*next;
}			t_arg_list;

typedef struct		s_cmd_list
{
  t_arg_list		*args;
  struct s_cmd_list	*next;
}			t_cmd_list;

typedef struct		s_redir_list
{
  t_redir_type		type;
  int			fd;
  char const		*name;
  struct s_redir_list	*next;
}			t_redir_list;

typedef struct		s_cmd
{
  char const		**tab;
  t_redir_list		*redir_list;
}			t_cmd;

typedef struct		s_arg_func
{
  char const		*rule;
  t_arg_list		*(*f)();
}			t_arg_func;

typedef struct		s_redir_func
{
  char const		*rule;
  t_redir_type		type;
}			t_redir_func;

typedef struct		s_index_list
{
  int			index;
  struct s_index_list	*next;
}			t_index_list;

t_cmd			*build_cmd(t_shell *shell, t_graph *graph);
t_arg_list		*build_comp_string(t_shell *shell, t_graph *graph);
t_redir_list		*build_redir(t_shell *shell, t_graph *graph);
t_arg_list		*build_substitution(t_shell *shell, t_graph *graph);
t_arg_list		*build_spe_string(t_shell *shell, t_graph *graph);
t_arg_list		*build_var(t_shell *shell, t_graph *graph);
t_arg_list		*the_concat(t_cmd_list *list);
t_arg_list		*(*is_comp_string(char const *str))();

t_index_list		*build_index(t_graph *graph);
bool			keep_index(t_index_list *list, int max, int index);

#endif /* end of include guard: BUILD_CMD_H_ */
