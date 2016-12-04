/*
** historic_init.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:20:00 2016 Nicolas Goudal
** Last update Thu Dec 01 10:57:22 2016
*/

#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "interface/historic_private.h"
#include "interface/interface_private.h"
#include "interface/error_define.h"

static char		*the_strcat(char *str1,
				    char *str2)
{
  char			*new;
  int			len1;
  int			len_tot;

  len1 = the_strlen(str1);
  len_tot = len1 + the_strlen(str2) + 1;
  if (!(new = realloc(str1, len_tot)))
    return (NULL);
  strcpy(new + len1, str2);
  return (new);
}

static t_istatus	historic_load_cmd_line(t_historic *historic,
					       char **str)
{
  int			len;
  char			*line;

  while ((len = strlen(*str))
	 && (*str)[len - 1] == '\\')
  {
    if (!(line = get_next_line(historic->fd)))
      return (S_SUCCESS);
    if (!(*str = the_strcat(*str, "\n"))
       || !(*str = the_strcat(*str, line)))
      return (S_FAILURE);
    free(line);
  }
  return (S_SUCCESS);
}

static t_istatus	historic_load(t_historic *historic)
{
  char			*str;
  t_historic_dir_list	*dir;
  int			length;

  dir = NULL;
  length = strlen(HISTO_PATH_SCOPE);
  while ((str = get_next_line(historic->fd)))
  {
    if (!!historic_load_cmd_line(historic, &str))
      return (S_FAILURE);
    if (!(strncmp(HISTO_PATH_SCOPE, str, length)))
    {
      if (!(dir = historic_get_dir(&historic->dir, str + length))
	  && !(dir = historic_new_dir(&historic->dir,
				      strdup(str + length))))
	return (S_FAILURE);
      historic->cur = dir;
    }
    else
      historic_new_cmd(historic->dir, strdup(str));
    free(str);
  }
  return (S_SUCCESS);
}

void			historic_init(t_historic *historic)
{
  if ((historic->fd = open(HISTO_FILE_PATH HISTO_FILE_NAME,
			   O_RDWR | O_APPEND)) == -1)
    return ;
  historic_load(historic);
}
