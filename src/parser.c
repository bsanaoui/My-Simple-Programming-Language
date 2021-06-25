#include "include/parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser = ft_calloc(1, sizeof(struct s_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->prev_token = parser->current_token;

	return (parser);
}

void		parser_eat(t_parser *parser, int token_type)
{
	if ((int)(parser->current_token->type) == token_type)
	{
		parser->prev_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	else
	{
		printf("Unexepected token '%s', with type %d\n",
				parser->current_token->value,
				parser->current_token->type
				);
		exit(1);
	}
}

t_ast		*parser_parse(t_parser *parser)
{
	return (parser_parse_statements(parser));
}

t_ast		*parser_parse_statement(t_parser *parser)
{
	if (parser->current_token->type == TOKEN_ID)
		return (parser_parse_id(parser));
	return (init_ast(AST_NOOP));
}

t_ast		*parser_parse_statements(t_parser *parser)
{
	t_ast	*compound = init_ast(AST_COMPOUND);
	compound->compound_value = ft_calloc(1, sizeof(struct s_ast*));
	t_ast	*ast_statement = parser_parse_statement(parser);
	compound->compound_value[0] = ast_statement;
	compound->compound_size += 1;
	while (parser->current_token->type == TOKEN_SEMI)
	{
		parser_eat(parser, TOKEN_SEMI);
		ast_statement = parser_parse_statement(parser);
		if (ast_statement)
		{
			compound->compound_size += 1;
			compound->compound_value = ft_realloc(
				compound->compound_value,
				compound->compound_size * sizeof(struct s_ast*));
			compound->compound_value[compound->compound_size - 1] = ast_statement;
		}
	}
	return (compound);
}

t_ast		*parser_parse_expr(t_parser *parser)
{
	if (parser->current_token->type == TOKEN_STRING)
		return	(parser_parse_string(parser));
	if (parser->current_token->type == TOKEN_ID)
		return	(parser_parse_id(parser));
	return (init_ast (AST_NOOP));
}

t_ast		*parser_parse_function_call(t_parser *parser)
{
	t_ast	*function_call = init_ast(AST_FUNCTION_CALL);
	function_call->fuction_call_name = parser->prev_token->value;
	parser_eat(parser, TOKEN_LPAREN);
	function_call->function_call_arguemnts = ft_calloc(1, sizeof(struct s_ast*));

	t_ast	*ast_expr = parser_parse_expr(parser);
	function_call->function_call_arguemnts[0] = ast_expr;
	function_call->function_call_arguments_size += 1;

	while (parser->current_token->type == TOKEN_COMMA)
	{
		parser_eat(parser, TOKEN_COMMA);

		ast_expr = parser_parse_expr(parser);
		function_call->function_call_arguments_size += 1;
		function_call->function_call_arguemnts = ft_realloc(
			function_call->function_call_arguemnts,
			function_call->function_call_arguments_size * sizeof(struct s_ast *));
		function_call->function_call_arguemnts[function_call->function_call_arguments_size - 1] = ast_expr;
		
	}
	parser_eat(parser, TOKEN_RPAREN);
	return (function_call);
}

t_ast		*parser_parse_variable_definition(t_parser *parser)
{
	char	*variable_definition_variable_name;

	parser_eat(parser, TOKEN_ID); //var
	variable_definition_variable_name = parser->current_token->value;
	parser_eat(parser, TOKEN_ID); //var name
	parser_eat(parser, TOKEN_EQUALS);
	t_ast	*variable_definition_value = parser_parse_expr(parser);
	t_ast	*variable_definition = init_ast(AST_VARIABLE_DEFINITION); 
	variable_definition->variable_definition_variable_name = variable_definition_variable_name;
	variable_definition->variable_definition_value = variable_definition_value;
	return (variable_definition);
}

t_ast		*parser_parse_variable(t_parser *parser)
{
	char	*token_value;
	token_value = parser->current_token->value;
	parser_eat(parser, TOKEN_ID); // var name or function call
	if (parser->current_token->type == TOKEN_LPAREN)
		return (parser_parse_function_call(parser));
	t_ast	*ast_variable = init_ast(AST_VARIABLE);
	ast_variable->variable_name = token_value;
	return (ast_variable);
}

t_ast		*parser_parse_string(t_parser *parser)
{
	t_ast	*ast_string = init_ast(AST_STRING);
	ast_string->string_value = parser->current_token->value;
	parser_eat(parser, TOKEN_STRING);
	return (ast_string);
}

t_ast		*parser_parse_id(t_parser *parser)
{
	if (ft_strcmp(parser->current_token->value, "var") == 0)
		return (parser_parse_variable_definition(parser));
	else
		return (parser_parse_variable(parser)); //without type
}