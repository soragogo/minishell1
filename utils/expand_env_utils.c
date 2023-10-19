/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:32:16 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 21:15:49 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	caliculate_incriment(char *prev)
{
	int	prev_len;

	if (ft_strncmp(prev, "$?", 2) == 0)
		prev_len = ft_strlen("$?");
	else
		prev_len = ft_strlen("${?}");
	return (prev_len);
}

void	free_all(char *tmp, char *a_st, char *arg)
{
	free(tmp);
	free(a_st);
	free(arg);
}

char	*deal_status(char *arg, int *i, int status, char *ret)
{
	char	*a_st;
	char	*tmp;
	char	*joined;
	char	*rest;

	if (status == -1)
		a_st = ft_strdup("[pid]");
	else
		a_st = ft_itoa(status);
	if (ft_strncmp(ret, "status", 6) == 0)
	{
		*i += caliculate_incriment(&arg[*i]);
		return (a_st);
	}
	joined = ft_substr(arg, 0, *i);
	tmp = ft_strjoin(joined, a_st);
	free(joined);
	rest = &arg[*i] + 2;
	if (ft_strncmp(&arg[*i], "${", 2) == 0)
		rest += 2;
	*i += ft_strlen(a_st);
	joined = ft_strjoin(tmp, rest);
	free_all(tmp, a_st, arg);
	return (joined);
}

int	return_end_of_env(char *end)
{
	int	i;

	i = 0;
	if (ft_isdigit(end[i]))
	{
		while (ft_isdigit(end[i]))
			i++;
	}
	else if (end[i] == '{')
	{
		while (end[i] != '}' && end[i])
			i++;
		if (end[i] == '}')
			i++;
	}
	else if (end[i] == '?' || end[i] == '$')
		i++;
	else
	{
		while (end[i] && (ft_isalnum(end[i]) || end[i] == '_'))
			i++;
	}
	return (i);
}
