/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/31 15:54:07 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

t_commandset	*process_tokens(t_token *tokens)
{
	int				num_of_commands;
	t_commandset	*commandsets;

	num_of_commands = count_commandset(tokens);
	commandsets = create_command_pipeline(num_of_commands);
	import_command(tokens, commandsets, num_of_commands);
	import_redirection(tokens, commandsets, num_of_commands);
	return (commandsets);
}

int	count_nonempty_tokens(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].arg != NULL)
	{
		if (tokens[i].arg[0] != '\0')
			count++;
		i++;
	}
	return (count);
}

void	import_nonempty_token(t_token *new_tokens, t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[j].arg != NULL)
	{
		if (tokens[j].arg[0] != '\0')
		{
			new_tokens[i].arg = ft_strdup(tokens[j].arg);
			i++;
		}
		j++;
	}
	new_tokens[i].arg = NULL;
}

t_token	*remove_empty_tokens(t_token *tokens)
{
	int		count;
	t_token	*new_tokens;

	count = count_nonempty_tokens(tokens);
	if (count == 0)
		return (NULL);
	new_tokens = (t_token *)ft_calloc(sizeof(t_token), count + 1);
	if (!new_tokens)
		return (NULL);
	import_nonempty_token(new_tokens, tokens);
	return (new_tokens);
}
