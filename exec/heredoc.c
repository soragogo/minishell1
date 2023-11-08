/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 16:17:57 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	write_to_pipe(int pipefd[2],
	char *line, const char *delimiter, t_info *info)
{
	int		i;
	int		d_len;
	char	*tmp;

	i = 0;
	d_len = ft_strlen(delimiter);
	if (only_space(line) == TRUE)
		return (0);
	i = skip_space(&line);
	while (i-- > 0)
		write(pipefd[1], " ", 1);
	tmp = ft_strdup(line);
	free(line);
	line = expand_quote(tmp,
			info->map_head, &(info->exit_status_log));
	if (ft_strncmp(line, delimiter, d_len + 1) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	free(line);
	return (0);
}

void	pipe_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
		exit(0);
	}
	if (signum == SIGINT)
	{
		g_sigstatus = SIGINT;
	}
}

void	handle_pipe_signals(void)
{
	signal(SIGINT, pipe_handler);
}

int	signal_check(void)
{
	if (g_sigstatus == SIGINT)
	{
		rl_replace_line("", 0);
		g_sigstatus = SIGINT;
		rl_done = 1;
	}
	return (0);
}

int	heredoc(const char *delimiter, t_info *info)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		rl_event_hook = signal_check;
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_sigstatus == SIGINT
			|| (ft_strlen(delimiter) == 0 && *line == '\0'))
		{
			free(line);
			break ;
		}
		if (write_to_pipe(pipefd, line, delimiter, info) == 1)
			break ;
		write(pipefd[1], "\n", 1);
	}
	if (close(pipefd[1]) == -1)
		error_message(NULL, ft_itoa(pipefd[1]), strerror(errno));
	return (pipefd[0]);
}
