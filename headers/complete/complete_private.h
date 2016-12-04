/*
** complete_private.h for PSU_2015_42sh in /Users/florian/Desktop/epitech/B2-PSU/PSU_2015_42sh/include
**
** Made by Florian Guyonnet
** Login   <guyonn_f@epitech.net>
**
** Started on  Tue May 31 14:41:08 2016 Florian Guyonnet
** Last update Thu Dec 01 15:35:02 2016
*/

#ifndef COMPLETE_PRIVATE_H_
# define COMPLETE_PRIVATE_H_

# include <stdbool.h>
# include "complete.h"
# include "the_parser/parser.h"
# include "shell/shell.h"
# include "interface/interface_complete.h"

/*
** tools
*/
int			complete_is_flag(char const *str);
char			*complete_get_folder_path(char const *path);
char			*complete_get_file_path(char const *path);
char			**complete_str_wordtab(char const *str);
t_complete_args		*complete_get_flag(char const *flag,
					   t_complete_args *args);

/*
** init
*/
t_complete		*complete_init();
t_status		complete_insert(char const **command_line,
					t_complete *complete);
t_status		complete_load(t_shell *complete,
				      char const *command_name);

/*
** event
*/
t_completion_list	*complete_on_event(t_shell *shell,
					   t_complete_command *command);

/*
** search
*/
t_status		complete_search_string(char const *command,
					       t_completion_list **list,
					       t_complete_args *flag);
t_status		complete_search_files(char const *path,
					      t_complete_type type,
					      t_completion_list **list);
t_status		complete_short_flag(char const *command,
					    t_complete *complete,
					    t_completion_list **list);
t_status		complete_long_flag(char const *command,
					   t_complete *complete,
					   t_completion_list **list);

/*
** completion_list
*/
t_completion_list	*complete_insert_comp(t_completion_list **list,
					      char const *str,
					      char const *desc);

#endif /* !COMPLETE_PRIVATE_H_ */
