#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

typedef struct s_visitor
{
	t_ast	**variable_definition;
	size_t	variable_definition_size;
}	t_visitor;

t_visitor	*init_visitor();
t_ast	*visitor_visit(t_visitor *visitor, t_ast *node);
t_ast	*visitor_visit_variable_definition(t_visitor *visitor, t_ast *node);
t_ast	*visitor_visit_variable(t_visitor *visitor, t_ast *node);
t_ast	*visitor_visit_function_call(t_visitor *visitor, t_ast *node);
t_ast	*visitor_visit_string(t_visitor *visitor, t_ast *node);
t_ast	*visitor_visit_compound(t_visitor *visitor, t_ast *node);

#endif