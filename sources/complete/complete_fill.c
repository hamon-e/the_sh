/*
** complete_fill.c for PSU_2015_42sh in sources/complete
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 23:33:55 2016 Nicolas Goudal
** Last update Thu Dec 01 10:53:22 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "tools/tools.h"
#include "opt_parser/opt.h"
#include "complete/complete.h"
#include "complete/complete_private.h"

static const t_opt_dico	g_opt_dico[] =
{
  {OPT_C, 'c', "command", true,
    offsetof(t_complete_args, command), OPT_TYPE_STRING},
  {OPT_S, 's', "short-option", true,
    offsetof(t_complete_args, short_option), OPT_TYPE_STRING},
  {OPT_L, 'l', "long-option", true,
    offsetof(t_complete_args, long_option), OPT_TYPE_STRING},
  {OPT_O, 'o', "old-option", true,
    offsetof(t_complete_args, old_option), OPT_TYPE_STRING},
  {OPT_D, 'd', "description", true,
    offsetof(t_complete_args, description), OPT_TYPE_STRING},
  {OPT_A, 'a', "arguments", true,
    offsetof(t_complete_args, string), OPT_TYPE_STRING},
  {OPT_E, 'e', "erase", false, 0, 0},
  {OPT_F, 'f', "no-files", false, 0, 0},
  {OPT_R, 'r', "require-parameter", false, 0, 0},
  {OPT_X, 'x', "exclusive", false, 0, 0},
  {0, 0, NULL, 0, 0, 0}
};

static t_status			complete_fill_arg_data(t_complete_args *new_arg,
						       t_opt *opt)
{
  if (opt->bit >= OPT_A)
  {
    new_arg->type = COMPLETE_TYPE_STRING;
    opt->bit -= OPT_A;
  }
  if (opt->bit >= OPT_D)
    opt->bit -= OPT_D;
  if (opt->bit >= OPT_O)
  {
    if (new_arg->long_option)
      free(new_arg->long_option);
    if (!(new_arg->long_option =
	  strdup(((t_complete_args *)opt->data)->old_option)))
      return (FAILURE);
    opt->bit -= OPT_O;
  }
  return (SUCCESS);
}

static void			complete_fill_arg_mod(t_complete_args *new_arg,
						      t_opt *opt)
{
  if (opt->bit >= OPT_X)
  {
    new_arg->type = COMPLETE_TYPE_FOLDERS;
    new_arg->no_file = true;
    new_arg->required = true;
    opt->bit -= OPT_X;
  }
  if (opt->bit >= OPT_R)
  {
    new_arg->required = true;
    opt->bit -= OPT_R;
  }
  if (opt->bit >= OPT_F)
  {
    new_arg->type = COMPLETE_TYPE_FOLDERS;
    new_arg->no_file = true;
    opt->bit -= OPT_F;
  }
  if (opt->bit >= OPT_E)
    opt->bit -= OPT_E;
}

static t_status			complete_get_opt(char const **args,
						 t_complete *complete,
						 t_complete_args *new_arg)
{
  t_opt				*opt;

  opt = opt_init(0, args, sizeof(t_complete_args), g_opt_dico);
  if (!opt)
    return (FAILURE);
  new_arg = opt->data;
  if (((t_complete *)opt->data)->name == NULL
      || strcmp(((t_complete *)opt->data)->name, complete->name) != 0)
    return (FAILURE);
  complete_fill_arg_mod(new_arg, opt);
  if (complete_fill_arg_data(new_arg, opt) == FAILURE)
    return (FAILURE);
  new_arg->next = complete->args;
  complete->args = new_arg;
  return (SUCCESS);
}

t_status			complete_insert(char const **commands,
						t_complete *complete)
{
  t_complete_args		*new_arg;

  if (complete->name == NULL
      || (new_arg = malloc(sizeof(t_complete_args))) == NULL)
    return (FAILURE);
  new_arg->type = COMPLETE_TYPE_BOTH;
  new_arg->required = false;
  new_arg->no_file = false;
  new_arg->short_option = NULL;
  new_arg->long_option = NULL;
  new_arg->string = NULL;
  new_arg->description = NULL;
  new_arg->next = NULL;
  if (*commands == NULL
      || complete_get_opt(commands + 1, complete, new_arg) == FAILURE)
  {
    free(new_arg);
    return (FAILURE);
  }
  return (SUCCESS);
}
