/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:42:39 by mayu              #+#    #+#             */
/*   Updated: 2023/10/29 00:10:08 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_name(char *ret, char *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	ret = ft_calloc(sizeof(char), i + 1);
	if (ret == NULL)
		fatal_error("malloc error");
	while (j < i)
	{
		ret[j] = env[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_env_value(char *ret, char *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	ret = ft_calloc(sizeof(char), ft_strlen(&env[i + 1]) + 1);
	if (ret == NULL)
		fatal_error("malloc error");
	while (env[i + j + 1] != '\0')
	{
		ret[j] = env[i + j + 1];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

size_t	count_env(t_env *env)
{
	size_t	count;

	count = 0;
	if (!(env))
		return (0);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	free_map(t_env **map)
{
	t_env	*env;
	t_env	*tmp;

	env = *map;
	if (!env)
		return ;
	while (env && env->next)
	{
		tmp = env->next;
		if (env->is_env == true)
		{
			free(env->name);
			free(env->value);
		}
		free(env);
		env = tmp;
	}
	if (env->is_env == true)
	{
		free(env->name);
		free(env->value);
	}
	free(env);
}
