/*
** err_interface.h for  in /home/lin_p/test/42sh/include
** 
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
** 
** Started on  Mon May 23 16:13:25 2016 Lin Patrick
** Last update Wed Jun  1 05:10:09 2016 Lin Patrick
*/

#ifndef ERR_DEFINE_H_
# define ERR_DEFINE_H_

# define MSG_ERR		"Error : "
# define MSG_WRNG		"Warning : "
# define MSG_WHILE		" while "

# define ERR_MALLOC		"allocation memory failed"
# define ERR_OPEN		"couldn't open file"
# define ERR_IOCTL		"ioctl failed"
# define ERR_IOCTL_WSZ		"getting window's size"
# define ERR_TCAPS		"%s termcaps could not be found"
# define ERR_ITF_INIT		"failure while initing the shell"
# define ERR_TCGETATTR		"couldn't get terminal property"
# define ERR_TCSETATTR		"couldn't properly set terminal"
# define ERR_SIGWINCH		"couldn't set a response to terminal resize"

#endif /* !ERR_DEFINE_H_ */
