/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commandset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:41 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/21 10:06:50 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int	count_commandset(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (tokens[0].arg != NULL)
		count++;
	while (tokens[i].arg != NULL)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return (count);
}

t_commandset	*create_command_pipeline(int num_of_commands)
{
	t_commandset	*commandsets;
	int				i;

	commandsets = ft_calloc(num_of_commands, sizeof(t_commandset));
	if (!commandsets)
		return (NULL);
	i = 1;
	commandsets[0].prev = NULL;
	if (num_of_commands > 1)
		commandsets[0].next = &commandsets[1];
	while (i < num_of_commands - 1)
	{
		commandsets[i].next = &commandsets[i + 1];
		commandsets[i].prev = &commandsets[i - 1];
		i++;
	}
	commandsets[num_of_commands - 1].next = NULL;
	if (num_of_commands > 1)
		commandsets[num_of_commands - 1].prev
			= &commandsets[num_of_commands - 2];
	i = 0;
	while (commandsets[i].next != NULL)
		i++;
	return (commandsets);
}

int	count_command(t_token *tokens, int current_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (current_cmd > 0)
	{
		while (tokens[i].arg && tokens[i].type != PIPE)
			i++;
		if (tokens[i].type == PIPE)
		{
			current_cmd--;
			i++;
		}
	}
	while (tokens[i].arg != NULL && tokens[i].type != PIPE)
	{
		if (tokens[i].type == COMMAND
			|| tokens[i].type == COMMAND_OPTION
			|| tokens[i].type == UNCATEGORIZED)
			count++;
		i++;
	}
	return (count);
}

// #include "token.h"
// #include <stdio.h>
// #include <libc.h>
// int main()
// {
// 	char *buff;
// 	int status = 0;
// 	while (1)
// 	{
// 		buff = readline("test here> ");
// 		ft_parser(buff, &status);
// 		free(buff);
// 	}
// }
