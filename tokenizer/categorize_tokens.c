/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:41 by ekamada           #+#    #+#             */
/*   Updated: 2023/11/01 10:05:20 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int	assign_redirection_type(t_token *token)
{
	if (ft_strncmp(token->arg, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(token->arg, ">", 2) == 0)
		return (REDIRECT_OUT);
	else if (ft_strncmp(token->arg, "<", 2) == 0)
		return (REDIRECT_IN);
	else if (ft_strncmp(token->arg, ">>", 3) == 0)
		return (APPEND_OUT);
	else if (ft_strncmp(token->arg, "<<", 3) == 0)
		return (HERE_DOCUMENT);
	return (-1);
}

int	assign_command_type(t_token *token, t_token *prev_token, int *command_flag)
{
	if (token->arg[0] == '-' && *command_flag == 1)
		return (COMMAND_OPTION);
	else if (prev_token == NULL
		|| (*command_flag == 0
			&& (prev_token->type < REDIRECT_OUT
				|| prev_token->type > HERE_DOCUMENT)))
	{
		*command_flag = 1;
		return (COMMAND);
	}
	else if (prev_token != NULL && prev_token->type >= REDIRECT_OUT
		&& prev_token->type <= HERE_DOCUMENT)
		return (FILE_NAME);
	else
		return (UNCATEGORIZED);
}

void	categorize_tokens(t_token *tokens)
{
	int	i;
	int	command_flag;
	int	type;

	i = 0;
	command_flag = 0;
	while (tokens[i].arg != NULL)
	{
		type = assign_redirection_type(&tokens[i]);
		if (type == -1)
		{
			if (i == 0)
				type = assign_command_type(&tokens[i],
						NULL, &command_flag);
			else
				type = assign_command_type(&tokens[i],
						&tokens[i - 1], &command_flag);
		}
		tokens[i].type = type;
		i++;
	}
}
