/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:32 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 13:29:08 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

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
