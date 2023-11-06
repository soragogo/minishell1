/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/06 20:10:21 by emukamada        ###   ########.fr       */
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
}


void	here_document(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = heredoc(node->filename, info);
	// printf("here_document: %s\n", node->filename);
	// printf("node->oldfd: %d\n", node->oldfd);
	// printf("node->newfd: %d\n", node->newfd);
	if (node->newfd == -1)
	{
		fatal_error(strerror(errno));
		info->exit_status_log = 1;
		return ;
	}
}
