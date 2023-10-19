#include "../includes/token.h"
#include "../includes/parser.h"
#include <stdbool.h>
#include <libc.h>

void write_syntax_error(void)
{
	const char *err1 = "minishell: syntax error\n";
	write(STDERR_FILENO,err1,ft_strlen(err1));
}

int redirect_error(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].arg)
	{
		if (tokens[i].type >= 2 && tokens[i].type <= 5)
		{
			if (!tokens[i+1].arg || (tokens[i + 1].type >= 2 && tokens[i + 1].type <= 5))
				return (1);
		}
		i++;
	}
	return 0;
}

int quote_error(t_token *tokens)
{
	int i = 0;
	int j;
	char quote;

	while (tokens[i].arg)
	{
		j = 0;
		while(tokens[i].arg[j])
		{
			if (tokens[i].arg[j] == '\'' || tokens[i].arg[j] == '\"')
			{
				quote = tokens[i].arg[j];
				j++;
				while (tokens[i].arg[j] != '\0' && tokens[i].arg[j] != quote)
					j++;
				if (tokens[i].arg[j] != quote)
				{
					quote = tokens[i].arg[j];
					return (1);
				}
			}
			j++;

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
				return (1);
			flag = 0;
		}
		else if (tokens[i].type != PIPE)
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (1);
	return 0;
}

int	bracket_error(t_token *tokens, char left_bracket, char right_bracket)
{
	int i;
	int j;
	bool inside_bracket;

	i = 0;
	inside_bracket = false;
	while (tokens[i].arg)
	{
		j = 0;
		while (tokens[i].arg[j])
		{
			if (tokens[i].arg[j] == left_bracket)
			{
				if (inside_bracket)
					return (1);
				inside_bracket = !inside_bracket;
			}
			else if (tokens[i].arg[j] == right_bracket)
			{
				if (!inside_bracket)
					return (1);
				inside_bracket = !inside_bracket;
			}
			j++;
		}
		i ++;
	}
	if (inside_bracket)
		return (1);
	return (0);
}


int syntax_error(t_token *tokens)
{
	if (pipe_error(tokens))
		write_syntax_error();
	else if (quote_error(tokens))
		write_syntax_error();
	else if (redirect_error(tokens))
		write_syntax_error();
	else if (bracket_error(tokens, '{', '}'))
		write_syntax_error();
	else if (bracket_error(tokens, '(', ')'))
		write_syntax_error();
	else
		return (0);
	return (1);
}
