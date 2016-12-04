/*
** complete.h for PSU_2015_42sh in include/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:46:24 2016 Nicolas Goudal
** Last update Sun Jun 05 23:46:45 2016 Nicolas Goudal
*/

#ifndef COMPLETE_H_
# define COMPLETE_H_

# include <stdbool.h>

# define DIR_COMPLETE		"./files/complete"
# define COMPLETE_EXT		".fish"

typedef enum			e_complete_type
{
  COMPLETE_TYPE_FILES,
  COMPLETE_TYPE_FOLDERS,
  COMPLETE_TYPE_STRING,
  COMPLETE_TYPE_BOTH
}				t_complete_type;

typedef enum			e_complete_flags
{
  OPT_C = 1,
  OPT_S = 2,
  OPT_L = 4,
  OPT_O = 8,
  OPT_D = 16,
  OPT_A = 32,
  OPT_E = 64,
  OPT_F = 128,
  OPT_R = 256,
  OPT_X = 512
}				t_complete_flags;

typedef struct			s_complete_command
{
  char				*name;
  char				*actual;
  char				*before;
}				t_complete_command;

typedef struct			s_complete_args
{
  char				*command;
  t_complete_type		type;
  bool				required;
  bool				no_file;
  char				*short_option;
  char				*long_option;
  char				*old_option;
  char				*string;
  char				*description;
  struct s_complete_args	*next;
}				t_complete_args;

typedef struct			s_complete
{
  char				*name;
  t_complete_args		*args;
}				t_complete;

#endif /* end of include guard: COMPLETE_H_ */
