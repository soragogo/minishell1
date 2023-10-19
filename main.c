/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:16:54 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 16:13:14 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "tokenizer/token.h"
#include "tokenizer/parser.h"
#include <stdbool.h>

void	loop_commandline(t_info *info,
	char *command_buf, t_commandset *commands)
{
	while (1)
	{
		ft_signals();
		command_buf = ft_readline(info->map_head);
		if (!command_buf)
			break ;
		if (*command_buf == '\0' || only_space(command_buf))
		{
			free(command_buf);
			continue ;
		}
		commands = ft_parser(command_buf,
				&(info->exit_status_log), info->map_head);
		if (commands == NULL)
		{
			free(command_buf);
			continue ;
		}
		info->exit_status_log = handle_command(commands, info);
		free_before_closing(commands, command_buf);
	}
}

int	main(void)
{
	char			*command_buf;
	t_token			*tokens;
	t_info			info;
	t_commandset	*commands;

	envmap_init(&info.map_head);
	info.exit_status_log = 0;
	while (1)
	{
		loop_commandline(&info, command_buf, commands);
	}
	free_map(&info.map_head);
	return (0);
}
