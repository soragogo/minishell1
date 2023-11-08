/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 15:39:36 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	append(t_redirect *node, t_info *info)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->newfd == -1)
	{
		error_message(NULL, node->filename, strerror(errno));
		info->exit_status_log = 1;
		return (1);
	}
	return (0);
}

int	redirect_out(t_redirect *node, t_info *info)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->newfd == -1)
	{
		error_message(NULL, node->filename, strerror(errno));
		info->exit_status_log = 1;
		return (1);
	}
	return (0);
}

int	redirect_in(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = open(node->filename, O_RDONLY);
	if (node->newfd == -1)
	{
		error_message(NULL, node->filename, strerror(errno));
		info->exit_status_log = 1;
		return (1);
	}
	return (0);
}

int	here_document(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = heredoc(node->filename, info);
	if (node->newfd == -1)
	{
		error_message(NULL, node->filename, strerror(errno));
		info->exit_status_log = 1;
		return (1);
	}
	return (0);
}
