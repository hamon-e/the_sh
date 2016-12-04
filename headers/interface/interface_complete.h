/*
** interface_complete.h for PSU_2015_42sh in include/interface
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Jun 05 17:15:08 2016 Benoit Hamon
** Last update Sun Jun 05 17:15:30 2016 Benoit Hamon
*/

#ifndef INTERFACE_COMPLETE_H_
# define INTERFACE_COMPLETE_H_

# define INIT_MAX_ROW		4

typedef enum			e_completion_type
  {
    NO_COMPL,
    HISTO_COMPL,
    LINE_COMPL,
    TAB_COMPL
  }				t_completion_type;

typedef struct			s_completion_list
{
  char				*str;
  char const			*desc;
  int				length;
  struct s_completion_list	*next;
}				t_completion_list;

typedef struct			s_completion_buf
{
  t_completion_list		*list;
  t_completion_list		*selected;
  t_completion_list		*start;
  int				nbr_to_print;
  int				nbr_of_elem;
  int				nbr_per_line;
  int				length_per_completion;
  int				idx;
  int				len;
}				t_completion_buf;

typedef struct			s_cmd_completion
{
  t_completion_type		type;
  char const			*str;
  int				len;
  char const			*aff;
  int				aff_len;
  t_completion_buf		comp;
}				t_cmd_completion;

#endif /* end of include guard: INTERFACE_COMPLETE_H_ */
