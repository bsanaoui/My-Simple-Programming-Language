#include "include/lexer.h"
# include<stdlib.h>
# include<string.h>

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer = ft_calloc(1, sizeof(struct s_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
		lexer_advance(lexer);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespaces(lexer);
		if (ft_isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		if (lexer->c == '=')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))));
		if (lexer->c == ';')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))));
		if (lexer->c == '(')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))));
		if (lexer->c == ')')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))));
		if (lexer->c == ',')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))));
	}
	return (init_token(TOKEN_EOF, "\0"));
}

t_token	*lexer_collect_string(t_lexer *lexer)
{	
	char	*value;
	char	*s;

	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '"')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (ft_isalnum(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
