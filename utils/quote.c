/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:25 by mayu              #+#    #+#             */
/*   Updated: 2023/10/31 15:39:52 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

char	*deal_env(char *arg, int *i, t_env *env_head);
char	*deal_raw_env(char *arg, int *i, t_env *env_head);

void	deal_single_quote(char *arg, int *i)
{
	char	*start;
	char	*end;

	start = &arg[(*i)];
	end = start + 1;
	ft_memmove(start, end, ft_strlen(end) + 1);
	while (arg[*i] && arg[*i] != '\'')
		(*i)++;
	if (arg[*i] == '\'')
	{
		start = &arg[*i];
		end = start + 1;
		ft_memmove(start, end, ft_strlen(end) + 1);
	}
}

char	*deal_double_quote(char *arg, int *i, t_env *env_head, int *status)
{
	char	*rest;
	char	*expanded;
	char	*tmp;
	char	*joined;

	rest = NULL;
	expanded = NULL;
	while (arg[(*i)] && arg[(*i)] != '\"')
		(*i)++;
	tmp = ft_substr(arg, 0, *i);
	(*i)++;
	rest = ft_strchr(&arg[*i], '\"') + 1;
	expanded = expand_env(arg, *i, env_head, status);
	joined = ft_strjoin(tmp, expanded);
	free(tmp);
	tmp = ft_strjoin(joined, rest);
	free(joined);
	*i += ft_strlen(expanded) - 1;
	free(expanded);
	free(arg);
	return (tmp);
}

char	*expand_quote(char *arg, t_env *env_head, int *status)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		while (arg[i] && arg[i] != '\'' && arg[i] != '\"' && arg[i] != '$')
			i++;
		if (arg[i] == '\'')
			deal_single_quote(arg, &i);
		else if (arg[i] == '\"')
			arg = deal_double_quote(arg, &i, env_head, status);
		else if (ft_strncmp(&arg[i], "$?", 2)
			* ft_strncmp(&arg[i], "${?}", 4) == 0)
			arg = deal_status(arg, &i, *status, "arg");
		else if (ft_strncmp(&arg[i], "$$", 2)
			* ft_strncmp(&arg[i], "${$}", 4) == 0)
			arg = deal_status(arg, &i, -1, "arg");
		else if (arg[i] == '$')
			arg = deal_raw_env(arg, &i, env_head);
	}
	return (arg);
}
