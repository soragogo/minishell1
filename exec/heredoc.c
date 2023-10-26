/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 14:42:11 by mayu             ###   ########.fr       */
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

void	pipe_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
		exit(0);
	}
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_redisplay();
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(0);
	}
}

// void	handle_pipe_signals(void)
// {
// 	signal(SIGQUIT, pipe_handler);
// 	signal(SIGINT, pipe_handler);
// }

void		handle_signal(int signal)
{
	extern int		g_status;

	ft_putstr_fd(BACK_CURSOR, STDERR_FILENO);
	ft_putstr_fd(CLEAR_FROM_CURSOR, STDERR_FILENO);
	if (signal == SIGINT)
		ft_putstr_fd("\nminishell>", STDERR_FILENO);
}

int	heredoc(const char *delimiter, t_info *info)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	while (1)
	{
		// handle_pipe_signals();
		signal(SIGINT, handle_signal);
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
