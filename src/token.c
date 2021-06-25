#include "include/token.h"
#include <stdlib.h>

t_token	*init_token(int type, char *value)
{
	t_token	*token = malloc(sizeof(struct s_token));
	token->type = type;
	token->value = value;
	return (token);
}