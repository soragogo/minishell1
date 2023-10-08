#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

int quote_error(t_token *tokens)
{
	int i = 0;
	int j;
	char quote_char;
	while (tokens[i].arg)
	{
		j = 0;
		if (tokens[i].arg[0] == '\'' || tokens[i].arg[0] == '\"')
		{
			quote_char = tokens[i].arg[0];
			while (tokens[i].arg[j])
				j++;
			j--;
			if (tokens[i].arg[j] != quote_char || j == 0)
			{
				printf("minishell: syntax error: unexpected end of file\n");
				return 1;
			}
		}
		i++;
	}
	return 0;
}

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
	if (quote_error(tokens))
		return 1;
	return 0;
}
