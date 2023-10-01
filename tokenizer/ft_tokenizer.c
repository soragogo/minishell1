/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:44 by ekamada           #+#    #+#             */
/*   Updated: 2023/09/27 20:12:31 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdbool.h>

int is_dilimeter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

char *find_end_of_quote(char *command)
{
	char *tmp = command;
	char c = *command;

	tmp++;
	while (*tmp && *tmp != c)
		tmp++;
	tmp++;
	return (tmp);
}

char *find_end_of_arg(char *command)
{
	char *tmp = command;
	if (is_dilimeter(*tmp) == 1)
	{
		if (*tmp == '<' && *(tmp + 1) == '<')
			tmp++;
		else if (*tmp == '>' && *(tmp + 1) == '>')
			tmp++;
		return tmp;
	}
	else
	{
		while (is_dilimeter(*command) == 0 && *command != ' ' && *command)
		{
			if (*command == '\'' || *command == '\"')
				command = find_end_of_quote(command);
			else if (*command)
				command++;
		}
		command--;
		return (command);
	}
}

int count_tokens(char *command)
{
	int count;

	count = 0;
	while (*command)
	{
		while (*command == ' ')
			command++;
		if (*command)
			count++;
		command = find_end_of_arg(command);
		command++;
	}
	return (count);
}

void split_into_tokens(t_token * tokens, char *command, int num_of_tokens)
	{
		char *start;
		char *end;
		int i;

	i = 0;
	start = command;
	while (*start == ' ')
		start++;
	end = find_end_of_arg(command);
	while (i < num_of_tokens)
	{
		tokens[i].arg = ft_calloc(end - start + 2, sizeof(char));
		tokens[i].is_freed = 0;
		strlcpy(tokens[i].arg, start, end - start + 2);
		start = end + 1;
		while (*start == ' ')
			start++;
		if (*start)
			end = find_end_of_arg(start);
		i++;
	}
	tokens[i].arg = NULL;
}

t_token *ft_tokenizer(char *command)
{
	int num_of_tokens;
	t_token *tokens;

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
