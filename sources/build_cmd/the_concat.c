/*
** the_concat.c for PSU_2015_42sh in sources/build_cmd
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 19:32:41 2016 Nicolas Goudal
** Last update Thu Dec 01 15:38:12 2016
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"

static void		free_save(t_cmd_list *list)
{
  t_cmd_list		*tmp;

  while (list)
  {
    tmp = list;
    list = list->next;
    free(tmp);
  }
}

static char		*create_str(t_cmd_list *list)
{
  t_cmd_list		*tmp;
  char			*str;
  size_t		i;

  i = 0;
  tmp = list;
  while (tmp)
  {
    if (tmp->args)
      i += strlen(tmp->args->str);
    tmp = tmp->next;
  }
  if (!(str = malloc((i + 1) * sizeof(char))))
    return (NULL);
  i = 0;
  tmp = list;
  while (tmp)
  {
    if (tmp->args)
      strcpy(str + i, tmp->args->str);
    if (tmp->args)
      i += strlen(tmp->args->str);
    tmp = tmp->next;
  }
  return (str);
}

static void		move_in_list(t_cmd_list *list,
				     t_cmd_list *save,
				     int *offset)
{
  int			i;
  t_cmd_list		*tmp;
  t_cmd_list		*save_tmp;

  tmp = list;
  save_tmp = save;
  i = 0;
  while (++i <= *offset)
  {
    tmp = tmp->next;
    save_tmp = save_tmp->next;
  }
  if (!(tmp->args = (tmp->args ? tmp->args->next : NULL)))
  {
    tmp->args = save_tmp->args;
    if ((i = *offset - 1) >= 0)
    {
      move_in_list(list, save, &i);
      *offset = (i < 0 ? -1 : the_count(list, offsetof(t_cmd_list, next)) - 1);
    }
    else
      *offset = -1;
  }
}

static t_cmd_list	*make_save(t_cmd_list *list)
{
  t_cmd_list		*save;
  t_cmd_list		*tmp;

  save = NULL;
  while (list)
  {
    if (!(tmp = malloc(sizeof(t_cmd_list))))
      return (NULL);
    *tmp = (t_cmd_list){list->args, NULL};
    the_pushback((void **)&save, tmp, offsetof(t_cmd_list, next));
    list = list->next;
  }
  return (save);
}

t_arg_list		*the_concat(t_cmd_list *list)
{
  t_arg_list		*ret;
  t_arg_list		*elem;
  t_cmd_list		*save;
  int			offset;

  if (!list)
    return (NULL);
  if (!(save = make_save(list)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  ret = NULL;
  offset = the_count(list, offsetof(t_cmd_list, next)) - 1;
  while (offset >= 0)
  {
    if (!(elem = malloc(sizeof(t_arg_list)))
	|| !(elem->str = create_str(list)))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    elem->next = NULL;
    the_pushback((void **)&ret, elem, offsetof(t_arg_list, next));
    move_in_list(list, save, &offset);
  }
  free_save(save);
  return (ret);
}
