/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/05 22:51:44 by emukamada        ###   ########.fr       */
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
			redirect_out(tmp_node, info);
		else if (tmp_node->type == REDIRECT_IN)
			redirect_in(tmp_node, info);
		else if (tmp_node->type == APPEND_OUT)
			append(tmp_node, info);
		else if (tmp_node->type == HERE_DOCUMENT)
			here_document(tmp_node, info);
		tmp_node = tmp_node->next;
	}
	tmp_node = commands->node;
	while (tmp_node)
	{
		do_redirect(tmp_node);
		tmp_node = tmp_node->next;
	}

}

void	do_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	node->stashfd = dup(node->oldfd);
	if (node->stashfd == -1)
		fatal_error(strerror(errno));
	if (dup2(node->newfd, node->oldfd) == -1)
		fatal_error(strerror(errno));
}

void	undo_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	undo_redirect(node->next);
	if (dup2(node->stashfd, node->oldfd) == -1)
		fatal_error(strerror(errno));
	if (close(node->stashfd) == -1)
		fatal_error(strerror(errno));
	if (close(node->newfd) == -1)
		fatal_error(strerror(errno));
}
