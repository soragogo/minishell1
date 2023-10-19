/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:23:11 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 13:18:56 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

int	exit_error(char **command, int minus)
{
	if (is_num(command[1]) == 1
		|| check_overflow(command[1], minus, ft_strlen(command[1])) != 1)
	{
		error_message("exit", command[1], "numeric argument required");
		exit(255);
	}
	else if (command[2])
	{
		error_message("exit", NULL, "too many arguments");
		return (1);
	}
	return (0);
}

int	ft_exit(char **command, t_info *info)
{
	int		minus;
	int		status;

	status = 0;
	minus = 1;
	if (command[1] == NULL)
		status = info->exit_status_log;
	else
	{
		if (command[1][0] == '-')
			minus = -1;
		if (exit_error(command, minus) == 1)
			return (1);
		else
			status = ft_atol(command[1]) % 255;
		if (status < 0)
			status = 256 + status;
	}
	exit (status);
}
