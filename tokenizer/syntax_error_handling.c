#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

int pipe_error(t_token *tokens)
{
	int flag = 0;
	int i = 0;
	while (tokens[i].arg)
	{
		if (tokens[i].type == PIPE)
		{
			if (flag == 0)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			flag = 0;
		}
		else if (tokens[i].type != PIPE)
			flag = 1;
		i++;
	}
	if (flag == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return 0;
}


int syntax_error(t_token *tokens)
{
	if (pipe_error(tokens))
		return 1;
	return 0;
}
