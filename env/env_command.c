/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:42:39 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 19:55:06 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_env(t_env **env_head, char *name, char *value, bool is_env)
{
	t_env	*env;
	t_env	*new;

	new = NULL;
	env = *env_head;
	if (name == NULL)
		return (-1);
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			env_unset(env_head, env->name);
			break ;
		}
		env = env->next;
	}
	new = item_new(new, name, value);
	if (is_env == true)
		new->is_env = true;
	add_new(env_head, new);
	return (0);
}

char	*map_get(t_env **env_head, char *name)
{
	t_env	*env;

	env = *env_head;
	while (env && env->name)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_unsetenv(t_env **env_head, t_env *env, t_env *prev)
{
	prev->next = env->next;
	if (env == prev)
		*env_head = env->next;
	if (env->is_env == true)
	{
		free(env->name);
		free(env->value);
		env->name = NULL;
		env->value = NULL;
	}
	free(env);
	env = NULL;
}

void	env_unset(t_env **env_head, char *delete_env_key)
{
	t_env	*env;
	t_env	*prev;

	env = *env_head;
	prev = env;
	if (!delete_env_key)
		return ;
	while (env && env->name)
	{
		if (ft_strcmp(delete_env_key, env->name) == 0)
			break ;
		prev = env;
		env = env->next;
	}
	if (env)
	{
		free_unsetenv(env_head, env, prev);
	}
}
