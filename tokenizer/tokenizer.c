/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:43 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/21 11:51:54 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

char	*find_end_of_quote(char *command)
{
	char	quote_char;

	quote_char = *command;
	command++;
	while (*command && *command != quote_char)
		command++;
	if (*command)
		command++;
	return (command);
}

char	*find_end_of_arg(char *command)
{
	if (is_dilimeter(*command))
	{
		if ((*command == '<' && *(command + 1) == '<')
			|| (*command == '>' && *(command + 1) == '>'))
			command++;
		return (command);
	}
	while (*command && !is_dilimeter(*command)
		&& *command != ' ' && *command != '\t')
	{
		if (*command == '\'' || *command == '\"')
			command = find_end_of_quote(command);
		else
			command++;
	}
	return (command - 1);
}

int	count_tokens(char *command)
{
	int	count;

	count = 0;
	while (*command)
	{
		while (*command == ' ' || *command == '\t')
			command++;
		if (*command)
			count++;
		command = find_end_of_arg(command);
		command++;
	}
	return (count);
}

void	split_into_tokens(t_token *tokens, char *command, int num_of_tokens)
{
	char	*start;
	char	*end;
	int		i;

	start = skip_spaces(command);
	i = 0;
	while (i < num_of_tokens)
	{
		end = find_end_of_arg(start);
		tokens[i].arg = ft_calloc(end - start + 2, sizeof(char));
		strlcpy(tokens[i].arg, start, end - start + 2);
		start = skip_spaces(end + 1);
		i++;
	}
	tokens[i].arg = NULL;
}

t_token	*ft_tokenizer(char *command)
{
	int		num_of_tokens;
	t_token	*tokens;

	num_of_tokens = count_tokens(command);
	tokens = (t_token *)ft_calloc(num_of_tokens + 1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	split_into_tokens(tokens, command, num_of_tokens);
	return (tokens);
}

// #include <libc.h>
// int main()
// {
// 	t_token *result;
// 	char *command;
// 	while (1)
// 	{
// 		command = readline("test here> ");
// 		result = ft_tokenizer(command);
// 		for (int i = 0; result[i].arg != NULL; i++)
// 		{
// 			printf("arg: [%s]\n", result[i].arg);
// 			printf("type: [%d]\n", result[i].type);
// 		}
// 		free(command);
// 	}
// }
