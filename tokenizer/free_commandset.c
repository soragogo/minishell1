/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commandset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/20 00:07:40 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

void	free_commands(t_commandset *cset)
{
	int		j;
	char	*tmp_cmd;

	j = 0;
	tmp_cmd = cset->command[0];
	while (tmp_cmd)
	{
		tmp_cmd = cset->command[j + 1];
		free(cset->command[j]);
		j++;
	}
	free(cset->command);
}

void	free_redirections(t_commandset *cset)
{
	t_redirect	*tmp_redir1;
	t_redirect	*tmp_redir2;

	tmp_redir1 = cset->node;
	tmp_redir2 = cset->node;
	while (tmp_redir2)
	{
		tmp_redir2 = cset->node->next;
		free((char *)cset->node->filename);
		cset->node = tmp_redir2;
	}
	free(tmp_redir1);
}

void	free_commandset(t_commandset *csets)
{
	int	i;

	i = 0;
	while ((i != 0 && csets[i - 1].next != NULL) || i == 0)
	{
		free_commands(&csets[i]);
		free_redirections(&csets[i]);
		i++;
	}
	free(csets);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].arg)
	{
		free(tokens[i].arg);
		i++;
	}
	free(tokens);
}
