#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
	t_token	*prev_token;
} t_parser;

t_parser	*init_parser(t_lexer *lexer);
void		parser_eat(t_parser *parser, int token_type);
t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_statement(t_parser *parser);
t_ast		*parser_parse_statements(t_parser *parser);
t_ast		*parser_parse_expr(t_parser *parser);
t_ast		*parser_parse_function_call(t_parser *parser);
t_ast		*parser_parse_variable(t_parser *parser);
t_ast		*parser_parse_variable_definition(t_parser *parser);
t_ast		*parser_parse_variable(t_parser *parser);
t_ast		*parser_parse_string(t_parser *parser);
t_ast		*parser_parse_id(t_parser *parser);
#endif