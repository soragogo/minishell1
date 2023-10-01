#include "token.h"
#include <stdbool.h>

char *quoted_arg(int *num_of_args, char *command, char quote)
{
	char *tmp;

	tmp = command;
	tmp++;
	*num_of_args += 1;
	while (*tmp && *tmp != quote)
		tmp++;
	tmp++;
	return (tmp);
}

bool is_separator(char c)
{
	return (c && c != ' ' && c != '\'' && c != '\"' && c != '|');
}

void count_tokens(char *command, int *num_of_args)
{
	while (*command)
	{
		while (*command == ' ')
			command++;
		if (*command == 34 || *command == 39)
			command = quoted_arg(num_of_args, command, *command);
		else if (*command == '|')
		{
			*num_of_args += 1;
			command++;
		}
		else
		{
			if (*command != ' ' && *command)
			{
				*num_of_args += 1;
				command++;
				while (is_separator(*command))
					command++;
			}
		}
	}
}

char *tokenize_nonexpandable(t_token *tokens, char *command)
{
	int i;
	char *tmp;

	i = 0;
	tmp = command;
	tokens->type = NON_EXPANDABLE;
	tmp++;
	while (tmp[i] && tmp[i] != 39)
		i++;
	tokens->arg = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*tmp && *tmp != 39)
	{
		tokens->arg[i] = *tmp;
		tmp++;
		i++;
	}
	tokens->arg[i] = '\0';
	tmp++;
	return (tmp);
}

char *tokenize_quoted(t_token *tokens, char *command)
{
	int i;
	char *tmp;

	i = 0;
	tmp = command;
	tokens->type = EXPANDABLE_QUOTED;
	tmp++;
	while (tmp[i] && tmp[i] != 34)
		i++;
	tokens->arg = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*tmp && *tmp != 34)
	{
		tokens->arg[i] = *tmp;
		tmp++;
		i++;
	}
	tokens->arg[i] = '\0';
	tmp++;
	return (tmp);
}

char *tokenize_pipe(t_token *tokens, char *command)
{
	char *tmp;

	tmp = command;
	tmp++;
	tokens->type = PIPE;
	tokens->arg = malloc(sizeof(char) * 2);
	tokens->arg[0] = '|';
	tokens->arg[1] = '\0';
	return (tmp);
}

char *tokenize_expandable(t_token *tokens, char *command)
{
	int i;
	char *tmp;

	i = 0;
	tmp = command;
	tokens->type = EXPANDABLE;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	tokens->arg = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*tmp && *tmp != ' ' && *tmp != '|' && *tmp != '\'' && *tmp != '\"')
	{
		tokens->arg[i] = *tmp;
		i++;
		tmp++;
	}
	tokens->arg[i] = '\0';
	// printf("arg: [%s]\n", tokens->arg);
	return (tmp);
}

void ft_token_split(t_token *tokens, char *command, int num_of_tokens)
{
	int i;

	i = 0;
	// printf("num_of_tokens: %d\n", num_of_tokens);
	while (i < num_of_tokens)
	{
		while (*command == ' ')
			command++;
		if (*command == 39)
			command = tokenize_nonexpandable(&tokens[i], command);
		else if (*command == 34)
			command = tokenize_quoted(&tokens[i], command);
		else if (*command == '|')
			command = tokenize_pipe(&tokens[i], command);
		else
			command = tokenize_expandable(&tokens[i], command);
		// printf("command :[%s]\n", command);
		i++;
	}
	// printf("tokens :%d\n", i);
	tokens[i].arg = NULL;
}

t_token *ft_tokenizer(char *command)
{
	int num_of_tokens;
	t_token *tokens;

	num_of_tokens = 0;
	count_tokens(command, &num_of_tokens);
	tokens = (t_token *)malloc(sizeof(t_token) * (num_of_tokens + 1));
	ft_token_split(tokens, command, num_of_tokens);
	// printf("num_of_tokens: [%d]\n", num_of_tokens);
	// for (int i = 0; tokens[i].arg != NULL; i++)
	// {
	// 	puts("------------------");
	// 	printf("token[%d] :[%s]\n", i, tokens[i].arg);
	// 	if (tokens[i].type == 0)
	// 		puts("NON_EXPANDABLE ''");
	// 	if (tokens[i].type == 1)
	// 		puts("EXPANDABLE_QUOTED "
	// 			 "");
	// 	if (tokens[i].type == 2)
	// 		puts("PIPE |");
	// 	if (tokens[i].type == 3)
	// 		puts("EXPANDABLE 文字列");
	// }
	return (tokens);
}

// #include <libc.h>
// int main()
// {
// 	char *command;
// 	while (1)
// 	{
// 		command = readline("test here> ");
// 		ft_tokenizer(command);
// 		free(command);
// 	}

// 	//	for (int i = 0; result[i] != NULL; i++)
// 	//	{
// 	//		printf("arg: [%s]\n", result[i].arg);
// 	//		printf("type: [%d]\n", result[i].type);
// 	//	}
// }
