/*
** complete_str_wordtab.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:35:36 2016 Nicolas Goudal
** Last update Sun Jun 05 23:35:36 2016 Nicolas Goudal
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static int		count_words_number(char const *str)
{
  int			index;
  int			count;
  bool			is_quote;

  count = 0;
  index = 0;
  is_quote = false;
  if (str[0])
    count += 1;
  while (str[index])
  {
    if (is_quote == false)
    {
      if (index > 0 && str[index]
	  && str[index - 1] == ' ' && str[index] != ' ')
	count += 1;
    }
    if (str[index] == '\"')
      is_quote = (is_quote == true) ? false : true;
    index += 1;
  }
  return (count);
}

static int		count_next_word(char const *str, int *index)
{
  int			count;
  bool			is_quote;

  while (str[*index] && str[*index] == ' ')
    *index += 1;
  count = 0;
  is_quote = false;
  while (str[*index + count] && (str[*index + count] != ' ' || is_quote))
  {
    if (str[*index + count] == '\"')
      is_quote = (is_quote == true) ? false : true;
    count += 1;
  }
  if (is_quote == true)
    return (-1);
  return (count);
}

static char		*next_word(char const *str, int *index)
{
  char			*new;
  int			count;
  int			length_word;
  int			tmp;

  length_word = count_next_word(str, index);
  if (length_word == -1 || length_word == 0
      || (new = malloc(sizeof(char) * (length_word + 1))) == NULL)
    return (NULL);
  count = 0;
  tmp = 0;
  while (str[*index + count + tmp] && count + tmp < length_word)
  {
    if (str[*index + count + tmp] != '\"')
    {
      new[count] = str[*index + count + tmp];
      count += 1;
    }
    else
      tmp += 1;
  }
  new[count] = '\0';
  *index += count + tmp;
  return (new);
}

char			**complete_str_wordtab(char const *str)
{
  char			**tab;
  int			index;
  int			count;

  if (str == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(char *) * (count_words_number(str) + 1))) == NULL)
    return (NULL);
  index = 0;
  count = 0;
  while (str[index])
  {
    if ((tab[count] = next_word(str, &index)) == NULL)
      return (tab);
    count += 1;
  }
  tab[count] = NULL;
  return (tab);
}
