/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 17:10:22 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	write_to_pipe(int pipefd[2],
	char *line, const char *delimiter, t_info *info)
{
	int	i;
	int	flag;
	int	d_len;

	i = 0;
	flag = 0;
	d_len = ft_strlen(delimiter);
	if (only_space(line) == TRUE)
		return (0);
	i = skip_space(&line);
	while (i > 0)
	{
		write(pipefd[1], " ", 1);
		i--;
	}
	if (flag == 0)
		line = expand_quote(ft_strdup(line),
				info->map_head, &(info->exit_status_log));
	if (ft_strncmp(line, delimiter, d_len + 1) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	return (0);
}

int	heredoc(const char *delimiter, t_info *info)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strlen(delimiter) == 0 && *line == '\0')
		{
			free(line);
			break ;
		}
		if (write_to_pipe(pipefd, line, delimiter, info) == 1)
			break ;
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
