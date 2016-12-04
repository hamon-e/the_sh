/*
** print_signal.c for PSU_2015_42sh in sources/exec
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:20:24 2016 Benoit Hamon
** Last update Thu Dec 01 15:36:16 2016
*/

#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include "the_parser/parser.h"
#include "shell/shell.h"
#include "shell/build_cmd.h"
#include "shell/find.h"
#include "shell/exec_private.h"

static const t_signal	g_signal_dico[] =
{
  {SIGHUP, "SIGHUP", "Terminal hung up"},
  {SIGINT, "SIGINT", "Quit request from job control (^C)"},
  {SIGQUIT, "SIGQUIT", "Quit request from job control with core dump (^\\)"},
  {SIGILL, "SIGIL", "Illegal instruction"},
  {SIGTRAP, "SIGTRAP", "Trace or breakpoint trap"},
  {SIGABRT, "SIGABRT", "Abort"},
  {SIGBUS, "SIGBU", "Misaligned address error"},
  {SIGFPE, "SIGFPE", "Floating point exception"},
  {SIGKILL, "SIGKIL", "Forced quit"},
  {SIGUSR1, "SIGUSR1", "User defined signal 1"},
  {SIGUSR2, "SIGUSR2", "User defined signal 2"},
  {SIGSEGV, "SIGSEGV", "Address boundary error"},
  {SIGPIPE, "SIGPIPE", "Broken pipe"},
  {SIGALRM, "SIGALRM", "Timer expired"},
  {SIGTERM, "SIGTERM", "Polite quit request"},
  {SIGCHLD, "SIGCHLD", "Child process status changed"},
  {SIGCONT, "SIGCONT", "Continue previously stopped process"},
  {SIGSTOP, "SIGSTOP", "Forced stop"},
  {SIGTSTP, "SIGTSTP", "Stop request from job control (^Z)"},
  {SIGTTIN, "SIGTTIN", "Stop from terminal input"},
  {SIGTTOU, "SIGTTOU", "Stop from terminal output"},
  {SIGURG, "SIGURG", "Urgent socket condition"},
  {SIGXCPU, "SIGXCPU", "CPU time limit exceeded"},
  {SIGXFSZ, "SIGXFSZ", "File size limit exceeded"},
  {SIGVTALRM, "SIGVTALRM", "Virtual timer expired"},
  {SIGPROF, "SIGPROF", "Profiling timer expired"},
  {SIGWINCH, "SIGWINCH", "Window size change"},
  {SIGIO, "SIGIO", "I/O on asynchronous file descriptor is possible"},
#ifdef SIGPWR
  {SIGPWR, "SIGPWR", "Power failure"},
#endif
  {SIGSYS, "SIGSY", "Bad system call"},
#ifdef SIGSTKFLT
  {SIGSTKFLT, "SISTKFLT", "Stack fault"},
#endif
  {SIGIOT, "SIGIOT", "Abort (Alias for SIGABRT)"},
#ifdef SIGUNUSED
  {SIGUNUSED, "SIGUNUSED", "Unused signal"},
#endif
  {0, 0, 0}
};

void	print_signal(char const *cmd, int status)
{
  int	i;

  i = 0;
  while (g_signal_dico[i].name && g_signal_dico[i].nbr != status)
    ++i;
  if (g_signal_dico[i].name && g_signal_dico[i].nbr != SIGINT)
    dprintf(2, "\"%s\" terminated by signal %s (%s)\n",
	    cmd,
	    g_signal_dico[i].name,
	    g_signal_dico[i].msg);
}
