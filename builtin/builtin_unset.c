/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:25:11 by mayu              #+#    #+#             */
/*   Updated: 2023/11/02 14:42:07 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	command_is_invalid(char *command)
{
	int	i;

	i = 1;
	if (!ft_isalpha(command[0]) && command[0] != '_')
		return (1);
	while (command[i])
	{
		if (!ft_isalnum(command[i]) && command[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_env **env_head, char **commands)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (commands[i] != NULL)
	{
		if (command_is_invalid(commands[i]))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(commands[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid indentifier", STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			ret = 1;
		}
		else
			env_unset(env_head, commands[i]);
		i++;
	}
	return (ret);
}
