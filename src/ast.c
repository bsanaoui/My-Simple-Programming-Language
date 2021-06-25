#include "include/ast.h"


t_ast	*init_ast(int type)
{
	t_ast	*ast = ft_calloc(1, sizeof(struct s_ast));
	ast->type = type;
	
	/* AST VARIABLE DEFINITION */
	ast->variable_definition_variable_name = NULL;
	ast->variable_definition_value = NULL;

	/* AST VARIABLE */
	ast->variable_name = NULL;

	/* AST FUNCTION CALL */
	ast->fuction_call_name = NULL;
	ast->function_call_arguemnts = NULL;
	ast->function_call_arguments_size = 0;

	/* AST STRING */
	ast->string_value = NULL;

	/* AST COMPOUND */
	ast->compound_value = NULL;
	ast->compound_size = 0;
	return (ast);
}
