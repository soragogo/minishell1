/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:37 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/21 11:51:43 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int	count_redirection(t_token *tokens, int current_pipe)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].arg && current_pipe)
	{
		if (tokens[i++].type == PIPE)
			current_pipe--;
	}
	if (tokens[i].type == PIPE)
		i++;
	while (tokens[i].arg && tokens[i].type != PIPE)
	{
		if (tokens[i].type >= REDIRECT_OUT && tokens[i].type <= HERE_DOCUMENT)
			count++;
		i++;
	}
	return (count);
}

void	connect_redirections(t_redirect *node, int count)
{
	int	i;

	i = 0;
	if (count <= 0)
		return ;
	node[0].prev = NULL;
	node[0].next = NULL;
	if (count > 1)
		node[0].next = &node[1];
	while (i < count - 1)
	{
		node[i].prev = &node[i - 1];
		node[i].next = &node[i + 1];
		i++;
	}
	if (count > 1)
	{
		node[count - 1].prev = &node[count - 2];
		node[count - 1].next = NULL;
	}
}

void	initialize_commandset(t_token *tokens,
	t_commandset *commandsets, int num_of_commands)
{
	int	i;
	int	count;

	i = 0;
	while (i < num_of_commands)
	{
		count = count_redirection(tokens, i);
		if (count == 0)
		{
			commandsets[i].node = NULL;
			i++;
			continue ;
		}
		commandsets[i].node = ft_calloc(count, sizeof(t_redirect));
		connect_redirections(commandsets[i].node, count);
		i++;
	}
}

void	populate_redirection(t_token *tokens,
	t_commandset *commandsets, int num_of_commands)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < num_of_commands)
	{
		while (tokens[j].arg && tokens[j].type != PIPE)
		{
			if (tokens[j].type >= REDIRECT_OUT
				&& tokens[j].type <= HERE_DOCUMENT
				&& tokens[j + 1].type == FILE_NAME)
			{
				commandsets[i].node[k].type = tokens[j].type;
				commandsets[i].node[k++].filename = ft_strdup(tokens[++j].arg);
			}
			j++;
		}
		if (tokens[j].type == PIPE && tokens[j + 1].arg)
			j++;
		i++;
		k = 0;
	}
}

void	import_redirection(t_token *tokens,
	t_commandset *commandsets, int num_of_commands)
{
	initialize_commandset(tokens, commandsets, num_of_commands);
	populate_redirection(tokens, commandsets, num_of_commands);
}
