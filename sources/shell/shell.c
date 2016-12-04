/*
** shell.c for PSU_2015_42sh in sources/shell
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 20:57:47 2016 Nicolas Goudal
** Last update Sun Dec 04 16:59:01 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include "opt_parser/opt.h"
#include "tools/msg.h"
#include "tools/tools.h"
#include "the_parser/rules.h"
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/exec.h"
#include "shell/init_shell.h"
#include "shell/functions.h"
#include "builtins/set.h"
#include "interface/interface.h"

void			shell_loop(t_shell *shell,
				   t_opt *opt,
				   char const *str)
{
  t_return		value;
  int			index;

  value = launch_parser(shell->grammar, str, &index);
  if (str[index] || !value.ok)
  {
    dprintf(2, "Syntax Error\n");
    shell->carry = false;
  }
  else
  {
    shell->stack = 0;
    if (opt && ((t_opt_shell *)opt->data)->debug == 2)
      print_parse(value.graph, 0);
    if (!opt || (opt->bit & OPT_EXECUTE) != OPT_EXECUTE)
      exec(shell, value.graph->detail);
  }
}

static int		shell_interface(void *lexer,
					t_shell *shell,
					t_opt *opt)
{
  t_interface		*interface;
  char const		*str;

  if (!(interface = interface_init(lexer, shell)))
    return (1);
  exec_no_args_functions(FUNCTIONS_INIT, shell);
  while (shell->exit == -1 && (str = interface_use(interface, shell->env)))
  {
    shell_loop(shell, opt, str);
    free_all_local_var(shell);
  }
  interface_quit(interface, shell->exit == -1 ? false : true);
  return (shell->exit == -1 ? !shell->carry : shell->exit);
}

static int		shell_no_interface(t_shell *shell,
					   t_opt *opt)
{
  char *str;

  while (shell->exit == -1 && (str = get_next_line(0)))
  {
    shell_loop(shell, opt, str);
    free(str);
  }
  return (shell->exit == -1 ? !shell->carry : shell->exit);
}

static int		launch_shell_opt(t_shell *shell,
					 t_opt *opt)
{
  t_opt_name		*file;

  file = opt->name;
  if (file)
  {
    while (file)
    {
      exec_file(shell, file->str);
      file = file->next;
    }
  }
  else
    shell_loop(shell, opt, ((t_opt_shell *)opt->data)->command);
  return (!shell->carry);
}

int			launch_shell(t_shell *shell,
				     t_opt *opt)
{
  void			*lexer;
  int			res;

  if (opt->name || (opt->bit &OPT_COMMAND) == OPT_COMMAND)
    res = launch_shell_opt(shell, opt);
  else if (isatty(0))
  {
    if (!(lexer = init_parser(DEFAULT_LEX, ((t_opt_shell *)opt->data)->debug)))
      return (1);
    res = shell_interface(lexer, shell, opt);
    end_parser(lexer);
  }
  else
    res = shell_no_interface(shell, opt);
  end_parser(shell->grammar);
  return (res);
}
