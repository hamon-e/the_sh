/*
** test.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun May 29 10:12:53 2016 Benoit Hamon
** Last update Sun Dec 04 17:13:14 2016 Benoit Hamon
*/

#ifndef TEST_H_
# define TEST_H_

typedef struct		s_test_func
{
  char const		*cmd;
  int			nbr;
  bool			(*f)();
}			t_test_func;

typedef enum		e_test_type
{
  TEST_OR,
  TEST_AND,
  TEST_CMD
}			t_test_type;

typedef struct		s_tree
{
  t_test_type		type;
  bool			reverse;
  char const		**cmd;
  bool			(*f)();
  struct s_tree		*left;
  struct s_tree		*right;
}			t_tree;

typedef struct		s_ope_func
{
  t_tree		*(*f)();
  t_test_type		type;
  char const		*cmd;
}			t_ope_func;

t_tree			*test_parser(char const ***argv, int index);

t_tree			*test_create_node(t_test_type type,
				     char const **cmd,
				     t_tree *left,
				     t_tree *right);

bool			test_eq(char const **str);
bool			test_ne(char const **str);
bool			test_gt(char const **str);
bool			test_ge(char const **str);
bool			test_lt(char const **str);
bool			test_le(char const **str);

bool			test_d(char const **str);
bool			test_b(char const **str);
bool			test_c(char const **str);
bool			test_e(char const **str);
bool			test_f(char const **str);
bool			test_g(char const **str);
bool			test_G(char const **str);
bool			test_L(char const **str);
bool			test_O(char const **str);
bool			test_p(char const **str);
bool			test_r(char const **str);
bool			test_s(char const **str);
bool			test_S(char const **str);
bool			test_t(char const **str);
bool			test_u(char const **str);
bool			test_w(char const **str);
bool			test_x(char const **str);

bool			test_equal(char const **str);
bool			test_nequal(char const **str);
bool			test_n(char const **str);
bool			test_z(char const **str);

#endif /* end of include guard: TEST_H_ */
