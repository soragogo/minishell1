/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/31 14:42:19 by emukamada        ###   ########.fr       */
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
		// printf("tokens[%d].arg: %s\n", i, tokens[i].arg);
		i++;
	}
}

static	t_commandset	*process_tokens(t_token *tokens)
{
	int				num_of_commands;
	t_commandset	*commandsets;

	// printf("%d\n", *status);
	// printf("%p\n", env_head);

	// expand_tokens(tokens, env_head, status);
	num_of_commands = count_commandset(tokens);
	commandsets = create_command_pipeline(num_of_commands);
	import_command(tokens, commandsets, num_of_commands);
	import_redirection(tokens, commandsets, num_of_commands);
	// free_tokens(tokens);
	return (commandsets);
}

int count_nonempty_tokens(t_token *tokens)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tokens[i].arg != NULL)
	{
		if(tokens[i].arg[0] != '\0')
			count++;
		i++;
	}
	return (count);
}

void import_nonempty_token(t_token *new_tokens, t_token *tokens)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(tokens[j].arg != NULL)
	{
		if (tokens[j].arg[0] != '\0')
		{
			new_tokens[i].arg = ft_strdup(tokens[j].arg);
			free(tokens[j].arg);
			// new_tokens[i].type = tokens[j].type;
			i++;
		}
		j++;
	}
	new_tokens[i].arg = NULL;
}

t_token *remove_empty_tokens(t_token *tokens)
{
    int count;
    t_token *new_tokens;

    count = count_nonempty_tokens(tokens);
	if (count == 0)
		return (NULL);
    new_tokens = (t_token *)ft_calloc(sizeof(t_token), count + 1); // +1 to include the NULL terminator
    if (!new_tokens)
        return (NULL);
    import_nonempty_token(new_tokens, tokens);
    return (new_tokens);
}

t_commandset	*ft_parser(char *buff, int *status, t_env *env_head)
{
	t_token			*tokens;
	t_token         *non_empty_tokens;

	tokens = ft_tokenizer(buff);
	expand_tokens(tokens, env_head, status);
 	non_empty_tokens = remove_empty_tokens(tokens);
	// for (int i = 0; non_empty_tokens[i].arg != NULL; i++)
	// {
	// 	if (non_empty_tokens[i].arg[0] == '\0')
	// 		// printf("non_empty_tokens[%d].arg: NULL\n", i);
	// 	else
	// 		// printf("non_empty_tokens[%d].arg: %s\n", i, non_empty_tokens[i].arg);
	// }
	if (!non_empty_tokens || (non_empty_tokens && non_empty_tokens[0].arg[0] == '\0'))
	{
		free(tokens);
		return (NULL);
	}
	categorize_tokens(non_empty_tokens);
	if (syntax_error(non_empty_tokens))
	{
		*status = 258;
		// non_empty_tokens を必要に応じて解放する
		free(tokens); // 元の tokens 配列を解放することを忘れないでください
		return (NULL);
	}
	else
	{
		t_commandset *result = process_tokens(non_empty_tokens);
		free(tokens); // 元の tokens 配列を解放することを忘れないでください
		return result;
	}
}
