/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/06 20:10:15 by emukamada        ###   ########.fr       */
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
	// printf("do_redirect: %s\n", node->filename);
	node->stashfd = dup(node->oldfd);
	// printf("node->stashfd(%d) = dup(node->oldfd)(%d)\n", node->stashfd, node->oldfd);
	if (node->stashfd == -1)
		fatal_error(strerror(errno));
	if (dup2(node->newfd, node->oldfd) == -1)
		fatal_error(strerror(errno));
	// printf("dup2(node->newfd(%d), node->oldfd(%d))\n", node->newfd, node->oldfd);
}

void	undo_redirect(t_redirect *node, int builtin)
{
	if (node == NULL)
		return ;
	undo_redirect(node->next, builtin);
	// puts("");
	// printf("undo_redirect: %s\n", node->filename);
	if (dup2(node->stashfd, node->oldfd) == -1)
		fatal_error(strerror(errno));
	// printf("dup2(node->stashfd(%d), node->oldfd)(%d)\n", node->stashfd, node->oldfd);
	// printf("close(node->stashfd): %d\n", node->stashfd);
	// printf("close(node->newfd): %d\n", node->newfd);
	if (close(node->stashfd) == -1)
	fatal_error(strerror(errno));
	if (close(node->newfd) == -1)
	fatal_error(strerror(errno));
}
