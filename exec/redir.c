/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 15:35:57 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

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

int	heredoc(const char *delimiter, t_info *info)
{
	int		pipefd[2];
	char	*line;
	int		count;
	size_t	d_len;
	int		i;
	int		flag;
	t_env	*env_head;

	count = 0;
	env_head = info->map_head;
	pipe(pipefd);
	d_len = ft_strlen(delimiter);
	if (d_len == 0)
		flag = 1;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (flag == 1 && *line == '\0')
		{
			free(line);
			break ;
		}
		if (only_space(line) == FALSE)
		{
			i = skip_space(&line);
			while (i > 0)
			{
				write(pipefd[1], " ", 1);
				i--;
			}
			if (flag == 0)
				line = expand_quote(line, env_head, &(info->exit_status_log));
			if (ft_strncmp(line, delimiter, d_len + 1) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
		}
		write(pipefd[1], "\n", 1);
		free(line);
		count++;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
