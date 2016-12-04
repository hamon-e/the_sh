/*
** rules.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Fri May 27 22:41:54 2016 Benoit Hamon
** Last update Wed Nov 30 17:49:53 2016
*/

#ifndef RULES_H_
# define RULES_H_

# define RULE_RANGE			"range"
# define RULE_ALL			"all"
# define RULE_CHAR			"char"

# define PARSER_ENTRY			"entry"

# define PARSER_CMD			"command"
#  define PARSER_SPE_STRING		"spe_string"
#   define PARSER_COMP_STRING		"comp_string"
#    define PARSER_STRING		"string"
#    define PARSER_INHIBITER		"inhibiter"
#    define PARSER_DOUBLE_QUOTE		"double_quotes"
#    define PARSER_SINGLE_QUOTE		"single_quotes"
#   define PARSER_SUBSTITUTION		"substitution"
#   define PARSER_VARIABLE		"variable"
#    define PARSER_VARNAME		"alphanum_string"
#    define PARSER_INDEX		"index"
#     define PARSER_RANGE		"range"
#     define PARSER_NUMBER		"number"
#  define PARSER_REDIR			"redirection"
#   define PARSER_REDIR_LEFT		"left_redir"
#   define PARSER_REDIR_RIGHT		"right_redir"
#   define PARSER_REDIR_DOUBLE_LEFT	"double_left_redir"
#   define PARSER_REDIR_DOUBLE_RIGHT	"double_right_redir"
#   define PARSER_FD			"fd_out"

# define PARSER_SCRIPT			"script"
#  define PARSER_IF			"if"
#   define PARSER_CONDITION		"condition"
#   define PARSER_ELSE			"else"
#  define PARSER_SWITCH			"switch"
#   define PARSER_CASE			"case"
#  define PARSER_FUNCTION		"function"
#  define PARSER_WHILE			"while"
#  define PARSER_FOR			"for"
# define PARSER_RESERVED		"reserved_end_key_word"
# define PARSER_RESERVED_NO		"reserved_key_word"
# define PARSER_RESERVED_END		"end"

# define PARSER_SEMICOLON_TCSH		"semi-colon_tcsh"
# define PARSER_OR_TCSH			"or_tcsh"
# define PARSER_AND_TCSH		"and_tcsh"

# define PARSER_COMBINERS		"combiners"
#  define PARSER_OR			"or"
#  define PARSER_AND			"and"
#  define PARSER_NOT			"not"
# define PARSER_PIPE			"pipeline"
# define PARSER_BGND			"bgnd"

# define ENV_EQUAL	'='
# define ENV_SEPARATOR	':'

# define DEFAULT_GRAMZ		"./files/gramz/tcsh.gramz"
# define DEFAULT_LEX		"./files/gramz/lexer.gramz"
# define FUNCTIONS_PATH		"./files/functions"
# define FUNCTIONS_INIT		"the_init"
# define FUNCTIONS_PROMPT	"the_prompt"
# define VAR_PATH		"PATH"
# define VAR_PWD		"PWD"

#endif /* end of include guard: RULES_H_ */
