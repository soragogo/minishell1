#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

void write_syntax_error(void)
{
	const char *err1 = "minishell: syntax error\n";
	write(STDERR_FILENO,err1,ft_strlen(err1));
}

int redirect_error(t_token *tokens)
{
	int i = 0;
	int type;
	char *redirect[] = {">", "<", ">>", "<<"};

	while (tokens[i].arg)
	{
		if (tokens[i].type >= 2 && tokens[i].type <= 5)
		{
			if (!tokens[i+1].arg || tokens[i + 1].type >= 2 && tokens[i + 1].type <= 5)
			{
				if (!tokens[i+1].arg)
					write_syntax_error();
				else
				{
					type = tokens[i + 1].type;
					write_syntax_error();
				}
				return 1;
			}

		}
		i++;
	}
	return 0;
}

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
			while (tokens[i].arg[j] != '\0' || tokens[i].arg[j] == '$')
				j++;
			j--;
			if (tokens[i].arg[j] != quote_char || j == 0)
			{
				write_syntax_error();
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
				write_syntax_error();
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
		write_syntax_error();
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
	if (redirect_error(tokens))
		return 1;
	return 0;
}
