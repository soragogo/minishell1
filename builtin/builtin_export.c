/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:13 by mayu              #+#    #+#             */
/*   Updated: 2023/10/28 21:31:23 by emukamada        ###   ########.fr       */
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
	int	i;
	int	result;

	result = 0;
	i = 1;
	if (!isalpha(name[0]) && name[0] != '_')
		result = 1;
	else
	{
		while (name[i])
		{
			if (!isalnum(name[i]) && name[i] != '_')
				result =  1;
			i++;
		}
	}
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

int	ft_export(t_env **map, char **commands)
{
	char	*name;
	char	*value;
	int		ret;

	name = NULL;
	value = NULL;
	ret = 0;
	if (commands[1] == NULL)
	{
		display_envlist(map);
		return (0);
	}

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
		name = get_env_name(name, *commands);
		if (name_is_invalid(name, 1))
		{
			ret = 1;
			continue ;
		}
		value = get_env_value(value, *commands);
		if (set_env(map, name, value, true) == -1)
		{
			error_message("export", NULL, "not a valid identifier");
			ret = 1;
		}
	}
	return (ret);
}
