/*
** interface_tools.c for PSU_2015_42sh in sources/ncurses
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:20:37 2016 Nicolas Goudal
** Last update Sun Jun 05 23:20:37 2016 Nicolas Goudal
*/

#include <stddef.h>

void		the_pushfront(void **list, void *elem, int n)
{
  *(char **)((char *)elem + n) = *list;
  *list = elem;
}

void		the_pushback2(void **list, void *elem,
			      size_t next, size_t prev)
{
  void		*tmp;

  if (*list)
  {
    tmp = *list;
    while (*(char **)((char *)tmp + next))
      tmp = *(char **)((char *)tmp + next);
    *(char **)((char *)tmp + next) = elem;
    *(char **)((char *)elem + prev) = tmp;
  }
  else
    *list = elem;
}

void		the_pushfront2(void **list, void *elem,
			       size_t next, size_t prev)
{
  *(char **)((char *)elem + prev) = NULL;
  *(char **)((char *)elem + next) = *list;
  if (*list)
    *(char **)((char *)(*list) + prev) = elem;
  *list = elem;
}
