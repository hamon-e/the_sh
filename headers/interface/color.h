/*
** color.h for  in /home/lin_p/PSU_2015_42sh/include/interface
** 
** Made by Lin Patrick
** Login   <lin_p@epitech.net>
** 
** Started on  Sat Jun  4 05:10:02 2016 Lin Patrick
** Last update Sun Jun  5 22:54:18 2016 Lin Patrick
*/

#ifndef COLOR_H_
# define COLOR_H_

typedef enum		s_using_color
  {
    DEFAULT_COLOR,
    RESERVED_COLOR,
    COMPL_COLOR,
    CMD_COLOR,
    ARG_COLOR,
    DQUOTE_COLOR,
    SQUOTE_COLOR,
    INHIB_COLOR,
    COMBINER_COLOR,
    VAR_COLOR,
    UNKNOWN_COLOR,
    END_COLOR
  }			t_using_color;

typedef enum		e_color_enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DGRAY,
    LRED,
    LGREEN,
    LYELLOW,
    LBLUE,
    LMAGENTA,
    LCYAN,
    LGRAY
  }			t_color_enum;

typedef struct		s_color_set
{
  char			*fgd;
  char			*bkg;
}			t_color_set;

typedef struct		s_color_set_tab
{
  char			*fgd;
  char			*bkg;
  char			*name;
}			t_color_set_tab;

#endif /* !COLOR_H_ */
