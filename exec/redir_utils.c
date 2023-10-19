/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 13:28:28 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

void	append(t_redirect *node)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	do_redirect(node);
}

void	redirect_out(t_redirect *node)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	do_redirect(node);
}

void	redirect_in(t_redirect *node)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = open(node->filename, O_RDONLY);
	do_redirect(node);
}

void	here_document(t_redirect *node, t_info *info)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = heredoc(node->filename, info);
	do_redirect(node);
}
