/*
** echo.c for PSU_2015_42sh in sources/builtins/echo
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Jun 02 17:33:27 2016 Benoit Hamon
** Last update Thu Dec 01 15:35:19 2016
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "tools/tools.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "builtins/echo.h"

static const t_echo_dico	g_echo_dico[] =
{
  {'n', OPT_NEWLINE},
  {'s', OPT_NO_SPACES},
  {'\0', 0}
};

static t_status		echo_option(char const *str,
				    int *opt,
				    bool *escape)
{
  int			i;
  int			j;

  i = 1;
  while (str[i])
  {
    j = 0;
    if (str[i] == 'e' || str[i] == 'E')
    {
      *escape = str[i++] == 'e' ? true : false;
      continue ;
    }
    while (g_echo_dico[j].c && g_echo_dico[j].c != str[i])
      ++j;
    if (!g_echo_dico[j].c)
      return (FAILURE);
    *opt |= g_echo_dico[j].type;
    ++i;
  }
  return (SUCCESS);
}

static void		echo_print(char const *word,
				   bool escape)
{
  int			i;
  int			j;
  int			ch;

  i = 0;
  while (word[i])
  {
    j = 0;
    if (word[i] == '\\' && word[i + 1] && escape)
    {
      if ((word[i + 1] == 'x' || word[i + 1] == '0')
	  && (ch = base_to_ascii(word, word[i + 1] == 'x'
				 ? BASE_16_X : BASE_8, &i)) != -1)
	printf("%c", ch);
      else
      {
	while (ESCAPE_SEQUENCE[j] && ESCAPE_SEQUENCE[j] != word[i + 1])
	  ++j;
	i += ESCAPE_SEQUENCE[j] ? printf("%c", j + '\a') + 1 : printf("%c", word[i]);
      }
    }
    else
      printf("%c", word[i++]);
  }
}

static void		echo_display(char const *argv[],
				     int const opt,
				     bool const escape)
{
  int			i;

  i = 0;
  while (argv[i])
  {
    echo_print(argv[i], escape);
    if ((opt & OPT_NO_SPACES) != OPT_NO_SPACES)
      printf(" ");
    ++i;
  }
  if ((opt & OPT_NEWLINE) != OPT_NEWLINE)
    printf("\n");
}

bool			the_echo(int argc,
				 char const *argv[])
{
  int			opt;
  bool			escape;

  opt = 0;
  escape = true;
  if (argc > 1 && *argv[1] == '-')
  {
    if (!!echo_option(argv[1], &opt, &escape))
      echo_display(argv + 1, opt, escape);
    else
      echo_display(argv + 2, opt, escape);
  }
  else
    echo_display(argv + 1, opt, escape);
  fflush(stdout);
  return (true);
}
