/*
** cd.h for  in /home/gusmin_m/Unix_System_programming/PSU_2015_42sh/include/builtins
** 
** Made by Matthieu Gusmini
** Login   <gusmin_m@epitech.eu>
** 
** Started on  Sat Jun  4 11:50:08 2016 
** Last update Sun Jun  5 21:35:34 2016 
*/

#ifndef BUILTIN_ERR_H_
# define BUILTIN_ERR_H_

# define CD_ERR "cd: "
# define SET_ERR "set: "
# define ECHO_ERR "echo: "
# define SET_COLOR_ERR "set_color: "

# define NO_DIRECTORY "The directory \"%s\" does not exist\n"
# define END_OF_HISTORY "Hit end of history...\n"

# define SET_WRONG_INDEX "Array index out of bounds\n"
# define SET_USAGE "set -({e | erase},(q | query},{n})[SCOPE] VARIABLE[INDEX]\n"

# define ECHO_USAGE ""

# define SET_COLOR_USAGE "set_color {-b} [COLOR]\n"

# define NO_ENV_VAR "\"%s\" is not set\n"

#endif /* end of include guard : CD_H_ */
