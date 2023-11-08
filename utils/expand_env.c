/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:32:16 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 18:34:34 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*deal_env(char *arg, int *i, t_env *env_head)
{
	char	*start;
	char	*env_value;
	char	*expanded;

	env_value = NULL;
	expanded = NULL;
	(*i)++;
	start = &arg[*i];
	*i += return_end_of_env(&arg[*i]);
	if (*start == '{')
		env_value = ft_substr(start, 1, ft_strchr(start, '}') - start - 1);
	else
		env_value = ft_substr(start, 0, &arg[*i] - start);
	expanded = map_get(&env_head, env_value);
	expanded = ft_strdup(expanded);
	free(env_value);
	return (expanded);
}

char	*deal_raw_env(char *arg, int *i, t_env *env_head)
{
	char	*tmp;
	char	*rest;
	char	*joined;
	char	*expanded;

	if (!arg[*i + 1] || (!ft_isalnum(arg[*i + 1]) && arg[*i + 1] != '_'))
	{
		(*i)++;
		return (arg);
	}
	joined = NULL;
	expanded = NULL;
	tmp = ft_substr(arg, 0, *i);
	rest = &arg[*i + 1] + return_end_of_env(&arg[*i + 1]);
	expanded = deal_env(arg, i, env_head);
	joined = ft_strjoin(tmp, expanded);
	free(tmp);
	tmp = ft_strjoin(joined, rest);
	free(joined);
	free(expanded);
	free(arg);
	return (tmp);
}

char	*handle_dollar(char *arg, int *i, t_env *env_head, int *status)
{
	char	*expanded;

	if (ft_strncmp(&arg[*i], "$?", 2) * ft_strncmp(&arg[*i], "${?}", 4) == 0)
		expanded = deal_status(arg, i, *status, "status");
	else if (!ft_isalnum(arg[*i + 1]) && arg[*i + 1] != '_')
	{
		(*i)++;
		expanded = ft_strdup("$");
	}
	else
		expanded = deal_env(arg, i, env_head);
	return (expanded);
}

char	*extract_not_env(char *arg, int *i, char **start)
{
	*start = &arg[*i];
	while (arg[*i] && arg[*i] != '\"' && arg[*i] != '$')
		(*i)++;
	return (ft_substr(*start, 0, &arg[*i] - *start));
}

char	*expand_env(char *arg, int i, t_env *env_head, int *status)
{
	char	*expanded;
	char	*tmp;
	char	*joined;
	char	*start;

	joined = NULL;
	while (arg[i] && arg[i] != '\"')
	{
		if (arg[i] == '$')
			expanded = handle_dollar(arg, &i, env_head, status);
		else
			expanded = extract_not_env(arg, &i, &start);
		tmp = ft_strdup(joined);
		free(joined);
		joined = ft_strjoin(tmp, expanded);
		free(tmp);
		free(expanded);
		expanded = NULL;
	}
	return (joined);
}
