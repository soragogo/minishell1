/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:13 by mayu              #+#    #+#             */
/*   Updated: 2023/11/01 10:41:10 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	display_envlist(t_env **env_head)
{
	t_env	*tmp;

	tmp = *env_head;
	if (tmp == NULL)
		return (0);
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
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	name_is_invalid(char *name, int should_free_name)
{
	int	result;

	result = 0;
	result = command_is_invalid(name);
	if (result == 1)
	{
		ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		if (should_free_name)
			free(name);
	}
	return (result);
}

int	add_env_variable(t_env **map, char *name, char *value)
{
	if (set_env(map, name, value, true) == -1)
	{
		error_message("export", NULL, "not a valid identifier");
		return (1);
	}
	return (0);
}

int	handle_export_commands(t_env **map, char **commands)
{
	char	*name;
	char	*value;
	int		ret;

	ret = 0;
	while (*(++commands) != NULL)
	{
		if (ft_strchr(*commands, '=') == NULL || !ft_strncmp(*commands, "=", 2))
		{
			if (name_is_invalid(*commands, 0))
				ret = 1;
			else if (set_env(map, ft_strdup(*commands), NULL, true) == -1)
				ret = 1;
			continue ;
		}
		name = get_env_name(NULL, *commands);
		if (name_is_invalid(name, 1))
		{
			ret = 1;
			continue ;
		}
		value = get_env_value(NULL, *commands);
		ret = add_env_variable(map, name, value);
	}
	return (ret);
}

int	ft_export(t_env **map, char **commands)
{
	if (commands[1] == NULL)
	{
		display_envlist(map);
		return (0);
	}
	return (handle_export_commands(map, commands));
}
