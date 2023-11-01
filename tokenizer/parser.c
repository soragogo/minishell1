/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/11/01 10:06:55 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

static void	expand_tokens(t_token *tokens, t_env *env_head, int *status)
{
	int	i;

	i = 0;
	while (tokens[i].arg)
	{
		skip_space(&(tokens[i].arg));
		tokens[i].arg = expand_quote(tokens[i].arg, env_head, status);
		i++;
	}
}

t_commandset	*ft_parser(char *buff, int *status, t_env *env_head)
{
	t_token			*tokens;
	t_token			*non_empty_tokens;
	t_commandset	*result;

	tokens = ft_tokenizer(buff);
	categorize_tokens(tokens);
	if (syntax_error(tokens))
	{
		*status = 258;
		free_tokens(tokens);
		return (NULL);
	}
	expand_tokens(tokens, env_head, status);
	non_empty_tokens = remove_empty_tokens(tokens);
	free_tokens(tokens);
	if (!non_empty_tokens
		|| (non_empty_tokens && non_empty_tokens[0].arg[0] == '\0'))
		return (NULL);
	categorize_tokens(non_empty_tokens);
	result = process_tokens(non_empty_tokens);
	free_tokens(non_empty_tokens);
	return (result);
}
