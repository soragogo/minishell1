/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 15:43:30 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	handle_redirection(t_commandset *commands, t_info *info)
{
	int			err;
	t_redirect	*tmp_node;

	err = 0;
	tmp_node = commands->node;
	while (tmp_node)
	{
		if (tmp_node->filename == NULL)
			return (0);
		if (tmp_node->type == REDIRECT_OUT)
			err = redirect_out(tmp_node, info);
		else if (tmp_node->type == REDIRECT_IN)
			err = redirect_in(tmp_node, info);
		else if (tmp_node->type == APPEND_OUT)
			err = append(tmp_node, info);
		else if (tmp_node->type == HERE_DOCUMENT)
			err = here_document(tmp_node, info);
		if (err == 1)
			return (1);
		tmp_node = tmp_node->next;
	}
	if (do_redirect(commands->node) == 1)
		return (1);
	return (0);
}

int	do_redirect(t_redirect *node)
{
	if (node == NULL)
		return (0);
	node->stashfd = dup(node->oldfd);
	if (node->stashfd == -1)
	{
		error_message(NULL, node->filename, strerror(errno));
		return (1);
	}
	if (dup2(node->newfd, node->oldfd) == -1)
	{
		error_message(NULL, NULL, strerror(errno));
		return (1);
	}
	do_redirect(node->next);
	return (0);
}

int	undo_redirect(t_redirect *node, int builtin)
{
	if (node == NULL)
		return (0);
	undo_redirect(node->next, builtin);
	if (dup2(node->stashfd, node->oldfd) == -1)
	{
		error_message(NULL, NULL, strerror(errno));
		return (1);
	}
	if (close(node->stashfd) == -1)
	{
		error_message(NULL, NULL, strerror(errno));
		return (1);
	}
	if (close(node->newfd) == -1)
	{
		error_message(NULL, NULL, strerror(errno));
		return (1);
	}
	return (0);
}
