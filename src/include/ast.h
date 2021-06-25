#ifndef AST_H
#define AST_H

#include "../libft/libft.h"

typedef struct s_ast
{
	enum {
		AST_VARIABLE_DEFINITION,
		AST_VARIABLE,
		AST_FUNCTION_CALL,
		AST_STRING,
		AST_COMPOUND, // MULTIPLE statements
		AST_NOOP // No operation
	} type;

	/* AST VARIABLE DEFINITION */
	char	*variable_definition_variable_name;
	struct s_ast	*variable_definition_value;

	/* AST VARIABLE */
	char	*variable_name;

	/* AST FUNCTION CALL */
	char	*fuction_call_name;
	struct	s_ast	**function_call_arguemnts;
	size_t	function_call_arguments_size;

	/* AST STRING */
	char	*string_value;

	/* AST COMPOUND */
	struct s_ast	**compound_value;
	size_t			compound_size;
}	t_ast;

t_ast	*init_ast(int type);
#endif