/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:16:54 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 17:57:53 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/token.h"
#include "includes/parser.h"
#include <stdbool.h>

int main()
{
	char *command_buf;
	// t_token *tokens;
	t_info info;
	t_commandset *commands;

	envmap_init(&info.map_head);
	info.exit_status_log = 0;
	while (1)
	{
		ft_signals();
		command_buf = ft_readline(info.map_head);
		if (!command_buf)
			break;
		if (*command_buf == '\0' || only_space(command_buf))
		{
			free(command_buf);
			continue ;
		}
		commands = ft_parser(command_buf, &(info.exit_status_log), info.map_head);
		if (commands == NULL)
		{
			free(command_buf);
			continue ;
		}

		info.exit_status_log = handle_command(commands, &info);
		free_before_closing(commands, command_buf);
	}
	free_map(&info.map_head);
	return (0);
}
