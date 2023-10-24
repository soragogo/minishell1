/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:45:48 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 21:17:22 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envmap_init(t_env **map)
{
	extern char	**environ;
	char		**env;
	char		*name;
	char		*value;

	*map = NULL;
	env = environ;
	while (*env)
	{
		name = get_env_name(name, *env);
		value = get_env_value(value, *env);
		set_env(map, name, value, true);
		env++;
	}
}

t_env	*item_new(t_env *new_env, char *name, char *value)
{
	new_env = ft_calloc(1, sizeof(*new_env));
	if (!new_env)
		fatal_error("malloc error");
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;
	new_env->is_env = false;
	return (new_env);
}

void	add_new(t_env **map, t_env *new_env)
{
	t_env	*env;

	env = *map;
	if (!env)
	{
		*map = new_env;
		return ;
	}
	else
	{
		while ((env)->next)
		{
			env = (env)->next;
		}
		(env)->next = new_env;
	}
	env->next = new_env;
}
