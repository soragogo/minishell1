/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:16:54 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 16:49:24 by mayyamad         ###   ########.fr       */
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
	if (!command_buf)
		return (0);
	if (*command_buf == '\0' || only_space(command_buf))
	{
		free(command_buf);
		return (1);
	}
	commands = ft_parser(command_buf,
			&(info->exit_status_log), info->map_head);
	// test_commandsets(commands, 2);
	if (commands == NULL)
	{
		free(command_buf);
		return (1);
	}
	info->exit_status_log = handle_command(commands, info);
	free_before_closing(commands, command_buf);
	return (1);
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
	while (1)
	{
		if (loop_commandline(&info, command_buf, commands) == 0)
			break ;
	}
	free_map(&info.map_head);
	return (0);
}
