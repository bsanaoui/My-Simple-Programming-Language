#include "include/visitor.h"
#include <stdio.h>

static t_ast	*builtin_function_print(t_visitor *visitor, t_ast **args, int args_size)
{
	int		i;
	t_ast	*visited_ast;

	i = 0;
	while (i < args_size)
	{
		visited_ast = visitor_visit(visitor, args[i]);
		if (visited_ast->type == AST_STRING)
			printf("%s\n", visited_ast->string_value);
		else
			printf("%p\n", visited_ast);
		i++;
	}
	return (init_ast(AST_NOOP));
}

t_visitor	*init_visitor()
{
	t_visitor	*visitor = ft_calloc(1, sizeof(struct s_visitor));
	visitor->variable_definition = NULL;
	visitor->variable_definition_size = 0;
	return (visitor);
}

t_ast	*visitor_visit(t_visitor *visitor, t_ast *node)
{
	//printf("type = %d\n",node->type);
	if (node->type == AST_VARIABLE_DEFINITION)
		return (visitor_visit_variable_definition(visitor, node));
	if (node->type == AST_VARIABLE)
		return (visitor_visit_variable(visitor, node));
	if (node->type == AST_FUNCTION_CALL)
		return (visitor_visit_function_call(visitor, node));
	if (node->type == AST_STRING)
		return (visitor_visit_string(visitor, node));
	if (node->type == AST_COMPOUND)
		return (visitor_visit_compound(visitor, node));
	if (node->type == AST_NOOP)
		return (node);
	printf("Uncaught statement of type '%d'\n", node->type);
	exit(1);
	return (init_ast(AST_NOOP));
}

t_ast	*visitor_visit_variable_definition(t_visitor *visitor, t_ast *node)
{
	if (!visitor->variable_definition)
	{
		visitor->variable_definition = ft_calloc(1, sizeof(struct s_ast*));
		visitor->variable_definition[0] = node;
		visitor->variable_definition_size += 1;
	}
	else
	{
		visitor->variable_definition_size += 1;
		visitor->variable_definition = ft_realloc(
			visitor->variable_definition,
			visitor->variable_definition_size * sizeof(struct s_ast*)
		);
		visitor->variable_definition[visitor->variable_definition_size - 1] = node;
	}
	return (node);
}

t_ast	*visitor_visit_variable(t_visitor *visitor, t_ast *node)
{
	size_t	i;
	t_ast	*vardef;

	i = 0;
	while (i < visitor->variable_definition_size)
	{
		vardef = visitor->variable_definition[i];
		if (ft_strcmp(vardef->variable_definition_variable_name, node->variable_name) == 0)
			return (visitor_visit(visitor, vardef->variable_definition_value));
		i++;
	}
	printf("Undefined variable '%s'\n", node->variable_name);
	return (node);
}

t_ast	*visitor_visit_function_call(t_visitor *visitor, t_ast *node)
{
	if (ft_strcmp(node->fuction_call_name, "print") == 0)
		return (builtin_function_print(visitor, node->function_call_arguemnts, node->function_call_arguments_size));
	printf ("undefined method '%s'\n", node->fuction_call_name);
	exit(1);
}

t_ast	*visitor_visit_string(t_visitor *visitor, t_ast *node)
{
	return (node);
	visitor->variable_definition_size = 0; //unused variabe
}

t_ast	*visitor_visit_compound(t_visitor *visitor, t_ast *node)
{
	size_t i;

	i = 0;
	while (i < node->compound_size)
	{
		// printf("%zu\n",i);
		visitor_visit(visitor, node->compound_value[i++]);
	}
		
	return (init_ast(AST_NOOP));
}