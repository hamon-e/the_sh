/*
** main.c for PSU_2015_42sh in sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:49:21 2016 Benoit Hamon
** Last update Sat Dec 03 14:08:16 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>
#include "opt_parser/opt.h"
#include "tools/tools.h"
#include "tools/msg.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/init_shell.h"

bool			g_signal = false;

void			handler(int __attribute__((unused))sig)
{
  g_signal = true;
}

static const t_opt_dico		g_opt_dico[] =
{
  {OPT_GRAMMAR, 'g', "grammar", true,
    offsetof(t_opt_shell, grammar), OPT_TYPE_STRING},
  {OPT_COMMAND, 'c', "command", true,
    offsetof(t_opt_shell, command), OPT_TYPE_STRING},
  {OPT_EXECUTE, 'n', "no-execute", false, 0, 0},
  {OPT_DEBUG, 'd', "debug", true,
    offsetof(t_opt_shell, debug), OPT_TYPE_NBR},
  {0}
};

int			main(int argc,
			     char const *argv[],
			     char const *envp[])
{
  t_opt			*opt;
  t_shell		shell;
  t_opt_shell		*data;

  signal(SIGINT, handler);
  signal(SIGQUIT, handler);
  if (!(opt = opt_init(argc, argv + 1, sizeof(t_opt_shell), g_opt_dico)))
  {
    dprintf(2, ERR_MSG_USAGE, argv[0]);
    return (1);
  }
  data = opt->data;
  shell.grammar = init_parser(data->grammar ? data->grammar : DEFAULT_GRAMZ,
			      data->debug);
  if (!shell.grammar || !init_shell(&shell, envp, opt->bit))
    return (1);
  return (launch_shell(&shell, opt));
}
