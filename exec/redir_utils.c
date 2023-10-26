/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 21:21:56 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

void	append(t_redirect *node, t_info *info)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->newfd == -1)
	{
		fatal_error(strerror(errno));
		info->exit_status_log = 1;
		return ;
	}
	do_redirect(node);
}

void	redirect_out(t_redirect *node, t_info *info)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->newfd == -1)
	{
		fatal_error(strerror(errno));
		info->exit_status_log = 1;
		return ;
	}
	do_redirect(node);
}

void	redirect_in(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = open(node->filename, O_RDONLY);
	if (node->newfd == -1)
	{
		fatal_error(strerror(errno));
		info->exit_status_log = 1;
		return ;
	}
	do_redirect(node);
}

void	here_document(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = heredoc(node->filename, info);
	if (node->newfd == -1)
	{
		fatal_error(strerror(errno));
		info->exit_status_log = 1;
		return ;
	}
	ft_signals();
	do_redirect(node);
}
