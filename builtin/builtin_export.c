/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:13 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 18:12:01 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	display_envlist(t_env **env_head)
{
	t_env	*tmp;

	tmp = *env_head;
	while (tmp)
	{
		if (tmp->name)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(tmp->value, STDOUT_FILENO);
				ft_putendl_fd("\"", STDOUT_FILENO);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	ft_export(t_env **map, char **commands)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (commands[1] == NULL)
	{
		display_envlist(map);
		return (0);
	}
	if (ft_strchr(commands[1], '=') == NULL)
	{
		return (0);
	}
	name = get_env_name(name, commands[1]);
	value = get_env_value(value, commands[1]);
	if (set_env(map, name, value, true) == -1)
	{
		error_message("export", NULL, "not a valid identifier");
		return (1);
	}
	return (0);
}
