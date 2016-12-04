/*
** msg.h for the_sh in headers/tools
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Dec 04 16:31:41 2016 Benoit Hamon
** Last update Sun Dec 04 16:32:55 2016 Benoit Hamon
*/

#ifndef HEADERS_TOOLS_MSG_H_
# define HEADERS_TOOLS_MSG_H_

# include "../../the_parser/headers_public/the_parser/msg.h"

# define ERR_MSG_USAGE		"Usage : %s --gramz --command -d -n {file}\n"
# define ERR_MSG_CMD		"Could not build command\n"
# define ERR_MSG_VARIABLE	"No Such Variable: %s\n"
# define ERR_MSG_INFINITE_LOOP	"Do you have an infinite loop ?\n"

#endif /* end of include guard: HEADERS_TOOLS_MSG_H_ */
