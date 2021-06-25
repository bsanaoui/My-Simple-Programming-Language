#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"

int	main()
{

	t_lexer *lexer = init_lexer(
		"var name1 = \"CMOS\";\n"
		"var name2 = \"bsanaoui\";\n"
		"print(name2);\n"
		"print(name1);\n"
	);
	
	// t_token	*token = lexer_get_next_token(lexer);;
	// while (token->type != TOKEN_EOF)
	// {
	// 	printf("TOKEN(%u, %s)\n", token->type, token->value);
	// 	token = lexer_get_next_token(lexer);
	// }
		
	
	t_parser	*parser = init_parser(lexer);
	t_ast		*root = parser_parse(parser);
	t_visitor	*visitor = init_visitor();
	visitor_visit(visitor, root);

	//printf("Type ast root = %d \nNumber of instructions = %zu\n", root->type, root->compound_size);
	return (0);
}
