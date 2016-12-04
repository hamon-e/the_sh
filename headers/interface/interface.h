/*
** interface_public.h for  in /home/lin_p/PSU_2015_42sh/include
**
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
**
** Started on  Mon May 30 16:39:42 2016 Lin Patrick
** Last update Thu Dec 01 20:54:16 2016 Benoit Hamon
*/

#ifndef INTERFACE_H_
# define INTERFACE_H_

# include <stdbool.h>
# include "the_parser/parser.h"
# include "shell/shell.h"
# include "interface/interface_private.h"
# include "interface/historic_private.h"

t_interface		*interface_init(void *lexer, t_shell *shell);
char const		*interface_use(t_interface *interface,
				       char * const env[]);
void			interface_quit(t_interface *interface,
				       bool is_new_cmd);

#endif /* !INTERFACE_H_ */
