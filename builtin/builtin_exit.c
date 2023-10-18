/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:23:11 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 18:11:46 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **command, t_info *info)
{
	int		status;

	status = 0;
	if (command[1] == NULL)
		status = info->exit_status_log;
	else if (command[2])
	{
		error_message("exit", NULL, "too many arguments");
		return (1);
	}
	else
	{
		if (is_num(command[1]) == 0)
		{
			error_message("exit", command[1], "numeric argument required");
			exit(255);
		}
		else
			status = ft_atoi(command[1]) % 255;
	}
	exit (status);
}
