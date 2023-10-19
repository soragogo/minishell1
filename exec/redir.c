/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 13:28:54 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

void	handle_redirection(t_commandset *commands, t_info *info)
{
	t_redirect	*tmp_node;

	tmp_node = commands->node;
	while (tmp_node)
	{
		if (tmp_node->filename == NULL)
			return ;
		if (tmp_node->type == REDIRECT_OUT)
			redirect_out(tmp_node);
		else if (tmp_node->type == REDIRECT_IN)
			redirect_in(tmp_node);
		else if (tmp_node->type == APPEND_OUT)
			append(tmp_node);
		else if (tmp_node->type == HERE_DOCUMENT)
			here_document(tmp_node, info);
		tmp_node = tmp_node->next;
	}
}

void	do_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	node->stashfd = dup(node->oldfd);
	dup2(node->newfd, node->oldfd);
}

void	undo_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	undo_redirect(node->next);
	dup2(node->stashfd, node->oldfd);
	close(node->stashfd);
	close(node->newfd);
}
