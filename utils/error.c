/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:04:08 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 18:17:51 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fatal_error(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	error_message(char *command, const char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	missing_file_error(char *command)
{
	error_message(command, NULL, "No such file or directory");
	exit(127);
}

void	set_err_status(t_commandset *commands, t_info *info)
{
	info->file_err = 1;
	if (!commands->next)
		info->exit_status_log = -1;
	commands->pid = -1;
}
