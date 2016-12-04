/*
** historic_private.h for  in /home/lin_p/PSU_2015_42sh/include
**
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
**
** Started on  Wed Jun  1 06:37:44 2016 Lin Patrick
** Last update Sun Jun 05 23:41:43 2016 Benoit Hamon
*/

#ifndef HISTORIC_PRIVATE_H_
# define HISTORIC_PRIVATE_H_

# define HISTO_FILE_PATH	"./files/"
# define HISTO_FILE_NAME	".historic"
# define HISTO_PATH_SCOPE	"dir="

typedef struct			s_historic_cmd_list
{
  char				*str;
  struct s_historic_cmd_list	*next;
  struct s_historic_cmd_list	*prev;
}				t_historic_cmd_list;

typedef struct			s_historic_dir_list
{
  char				*name;
  t_historic_cmd_list		*cmd;
  struct s_historic_dir_list	*next;
}				t_historic_dir_list;

typedef struct			s_historic
{
  int				fd;
  t_historic_dir_list		*dir;
  t_historic_dir_list		*cur;
  t_historic_cmd_list		*selected;
}				t_historic;

t_historic_dir_list		*historic_new_dir(t_historic_dir_list **list,
						  char *name);

t_historic_dir_list		*historic_get_dir(t_historic_dir_list **list,
						  char *dir);

int				historic_new_cmd(t_historic_dir_list *dir,
						 char *str);
void				historic_init(t_historic *historic);

#endif /* !HISTORIC_PRIVATE_H_ */
