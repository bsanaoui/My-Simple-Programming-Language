#ifndef TOKEN_H
#define TOKEN_H

#include "../libft/libft.h"

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_COMMA,
		TOKEN_EOF
	}	type;
	char	*value;
}	t_token;

t_token	*init_token(int type, char *value);

#endif