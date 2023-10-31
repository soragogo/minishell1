/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/31 13:07:39 by emukamada        ###   ########.fr       */
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
		printf("tokens[%d].arg: %s\n", i, tokens[i].arg);
		i++;
	}
}

static	t_commandset	*process_tokens(t_token *tokens,
	int *status, t_env *env_head)
{
	int				num_of_commands;
	t_commandset	*commandsets;

	printf("%d\n", *status);
	printf("%p\n", env_head);

	// expand_tokens(tokens, env_head, status);
	num_of_commands = count_commandset(tokens);
	commandsets = create_command_pipeline(num_of_commands);
	import_command(tokens, commandsets, num_of_commands);
	import_redirection(tokens, commandsets, num_of_commands);
	free_tokens(tokens);
	return (commandsets);
}

t_commandset	*ft_parser(char *buff, int *status, t_env *env_head)
{
	t_token			*tokens;

	tokens = ft_tokenizer(buff);
	expand_tokens(tokens, env_head, status);
	for (int i = 0; tokens[i].arg; i++)
		printf("tokens[%d]: %s\n", i, tokens[i].arg);
	categorize_tokens(tokens);
	if (syntax_error(tokens))
	{
		*status = 258;
		free_tokens(tokens);
		return (NULL);
	}
	else
		return (process_tokens(tokens, status, env_head));
}
