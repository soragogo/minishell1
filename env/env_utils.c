/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:45:48 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 20:39:23 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_space(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *str;
	while ((9 <= tmp[i] && tmp[i] <= 13) || tmp[i] == 32)
		i++;
	*str = &tmp[i];
	return (i);
}

char	*env_join(char *name, char *value, char **environ)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(name, "=");
	environ[0] = ft_strjoin(tmp, value);
	free(tmp);
	return (environ[0]);
}

char	**create_environ(t_env **env_head)
{
	t_env	*tmp;
	char	**environ;
	int		i;
	int		env_num;

	i = 0;
	tmp = *env_head;
	env_num = count_env(*env_head);
	environ = (char **)ft_calloc(sizeof(char *), env_num + 1);
	if (!environ)
		fatal_error("malloc error");
	while (tmp)
	{
		env_join(tmp->name, tmp->value, &environ[i]);
		tmp = tmp->next;
		i++;
	}
	environ[i] = NULL;
	return (environ);
}

void	free_environ(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
