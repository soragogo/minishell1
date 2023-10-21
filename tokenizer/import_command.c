/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/21 11:51:33 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int	process_token(t_token *tokens, int j, t_commandset *commandset, int k)
{
	if (tokens[j].type == COMMAND
		|| tokens[j].type == COMMAND_OPTION
		|| tokens[j].type == UNCATEGORIZED)
	{
		commandset->command[k] = ft_strdup(tokens[j].arg);
		k++;
	}
	return (k);
}

int	advance_to_next_token(t_token *tokens, int j)
{
	if (tokens[j].type == PIPE)
		j++;
	return (j);
}

void	import_command(t_token *tokens,
	t_commandset *commandsets, int num_of_commands)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	j = 0;
	while (i < num_of_commands)
	{
		count = count_command(tokens, i);
		commandsets[i].command = ft_calloc(count + 1, sizeof(char *));
		k = 0;
		while (tokens[j].arg != NULL && tokens[j].type != PIPE)
		{
			k = process_token(tokens, j, &commandsets[i], k);
			j++;
		}
		commandsets[i].command[k] = NULL;
		j = advance_to_next_token(tokens, j);
		i++;
	}
}
