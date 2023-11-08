/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:16:54 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 18:16:52 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/token.h"
#include "includes/parser.h"
#include <stdbool.h>

int	loop_commandline(t_info *info,
	char *command_buf, t_commandset *commands)
{
	ft_signals();
	command_buf = ft_readline();
	if (g_sigstatus == SIGINT)
		info->exit_status_log = 1;
	g_sigstatus = 0;
	if (!command_buf)
		return (0);
	if (*command_buf == '\0' || only_space(command_buf))
	{
		free(command_buf);
		return (1);
	}
	commands = ft_parser(command_buf,
			&(info->exit_status_log), info->map_head);
	if (commands == NULL)
	{
		free(command_buf);
		return (1);
	}
	handle_pipe_signals();
	handle_command(commands, info);
	if (g_sigstatus == SIGINT || g_sigstatus == 130 || g_sigstatus == 131)
		info->exit_status_log = g_sigstatus;
	free_before_closing(commands, command_buf);
	return (1);
}

int	main_signal_check(void)
{
	if (g_sigstatus == SIGINT)
	{
		g_sigstatus = SIGINT;
	}
	return (0);
}

int	main(void)
{
	char			*command_buf;
	t_info			info;
	t_commandset	*commands;

	command_buf = NULL;
	commands = NULL;
	envmap_init(&info.map_head);
	info.exit_status_log = 0;
	info.file_err = 0;
	while (1)
	{
		g_sigstatus = 0;
		if (loop_commandline(&info, command_buf, commands) == 0)
			break ;
		if (g_sigstatus == SIGINT)
			info.exit_status_log = 1;
	}
	free_map(&info.map_head);
	return (0);
}
