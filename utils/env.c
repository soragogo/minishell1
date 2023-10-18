/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:42:39 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 15:44:18 by mayu             ###   ########.fr       */
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
	ret = malloc(sizeof(char) * i + 1);
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
	ret = malloc(sizeof(char) * ft_strlen(&env[i + 1]) + 1);
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

t_env	*map_new(void)
{
	t_env	*map;

	map = ft_calloc(1, sizeof(*map));
	if (map == NULL)
		fatal_error("malloc error");
	return (map);
}

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

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

t_env	*item_new(t_env *new_env, char *name, char *value)
{
	new_env = ft_calloc(1, sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;
	new_env->is_env = false;
	return (new_env);
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

void	add_new(t_env **map, t_env *new_env)
{
	t_env	*env;

	env = *map;
	if (!env)
	{
		*map = new_env;
		return;
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
		prev->next = env->next;
		if (env->is_env == true)
		{
			free(env->name);
			free(env->value);
		}
		free(env);
		env = NULL;
	}
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

void	free_map(t_env **map)
{
	t_env	*env;
	t_env	*tmp;

	env = *map;
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
