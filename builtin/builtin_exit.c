/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:23:11 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 03:24:00 by mayu             ###   ########.fr       */
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

int	ft_exit(char **command, t_info *info)
{
	int		status;
	char	*arg;

	status = 0;
	if (command[1] == NULL)
		status = info->exit_status_log;
	else
	{
		if (is_num(command[1]) == 1)
		{
			error_message("exit", command[1], "numeric argument required");
			exit(255);
		}
		else if (command[2])
		{
			error_message("exit", NULL, "too many arguments");
			return (1);
		}
		else
			status = ft_atoi(command[1]) % 255;
		if (status < 0)
			status = 256 + status;
	}
	exit (status);
}
