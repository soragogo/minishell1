/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:27:00 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 10:42:59 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	is_builtin(t_commandset *command)
{
	static char	*builtin[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int			i;

	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strcmp(*command[0].command, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(t_commandset *commands, t_info *info)
{
	int	status;

	status = 0;
	if (handle_redirection(commands, info) == 1)
		return (1);
	if (ft_strncmp(*commands[0].command, "echo", 4) == 0)
		status = ft_echo(commands->command);
	else if (ft_strncmp(*commands[0].command, "cd", 3) == 0)
		status = ft_chdir(commands->command, &(info->map_head));
	else if (ft_strncmp(*commands[0].command, "env", 4) == 0)
		status = ft_env(&(info->map_head));
	else if (ft_strncmp(*commands[0].command, "pwd", 4) == 0)
		status = ft_pwd(info);
	else if (ft_strncmp(*commands[0].command, "export", 7) == 0)
		status = ft_export(&info->map_head, commands->command);
	else if (ft_strncmp(*commands[0].command, "unset", 6) == 0)
		status = ft_unset(&info->map_head, commands->command);
	else if (ft_strncmp(*commands[0].command, "exit", 5) == 0)
		status = ft_exit(commands->command, info);
	else
		return (-1);
	undo_redirect(commands->node, 1);
	return (status);
}
