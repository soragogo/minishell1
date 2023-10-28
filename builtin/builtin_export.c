/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:13 by mayu              #+#    #+#             */
/*   Updated: 2023/10/29 00:11:57 by mayu             ###   ########.fr       */
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

int	is_valid_name(char **name)
{
	int	i;

	i = 0;
	if (name[0][i] == '\0' || ft_isdigit(name[0][i]) == 1)
		return (1);
	while (name[0][i] != '\0')
	{
		if (name[0][i] == '_' || ft_isalnum(name[0][i]) == 1)
			i++;
		else
			return (1);
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
	name = get_env_name(name, commands[1]);
	value = get_env_value(value, commands[1]);
	if (set_env(map, name, value, true) == -1 || is_valid_name(&name) == 1)
	{
		error_message("export", NULL, "not a valid identifier");
		return (1);
	}
	if (ft_strchr(commands[1], '=') == NULL)
	{
		if (set_env(map, ft_strdup(commands[1]), NULL, true) == -1)
			return (1);
		return (0);
	}
	return (0);
}
