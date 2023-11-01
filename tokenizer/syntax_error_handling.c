/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/01 10:07:10 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int	redirect_error(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].arg)
	{
		if (tokens[i].type >= 2 && tokens[i].type <= 5)
		{
			if (!tokens[i + 1].arg
				|| (tokens[i + 1].type >= 2 && tokens[i + 1].type <= 5))
				return (1);
		}
		i++;
	}
	return (0);
}

int	quote_error(t_token *tokens)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (tokens[i].arg)
	{
		j = 0;
		while (tokens[i].arg[j])
		{
			if (tokens[i].arg[j] == '\'' || tokens[i].arg[j] == '\"')
			{
				quote = tokens[i].arg[j];
				j++;
				while (tokens[i].arg[j] != '\0' && tokens[i].arg[j] != quote)
					j++;
				if (tokens[i].arg[j] != quote)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	pipe_error(t_token *tokens)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
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
	return (0);
}

int	syntax_error(t_token *tokens)
{
	if (pipe_error(tokens)
		|| quote_error(tokens)
		|| redirect_error(tokens)
		|| bracket_error(tokens, '{', '}')
		|| bracket_error(tokens, '(', ')'))
	{
		write(STDERR_FILENO, "minishell: syntax error\n", 24);
		return (1);
	}
	return (0);
}
