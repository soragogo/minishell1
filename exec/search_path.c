/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:37:58 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 19:33:24 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include "../includes/minishell.h"

char	*split_path(char *file, char *start, char *end, int *flag)
{
	char	path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	if (end)
		ft_strlcpy(path, start, end - start + 1);
	else
	{
		*flag = 1;
		ft_strlcpy(path, start, ft_strlen(start) + 1);
	}
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, file, ft_strlen(path) + ft_strlen(file) + 1);
	if (access(path, F_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

char	*fetch_path(char *file, t_env **map)
{
	char	*start;
	char	*end;
	int		flag;

	flag = 0;
	end = NULL;
	start = map_get(map, "PATH");
	if (start == NULL)
		return (NULL);
	while (flag == 0)
	{
		if (end != NULL && *(end + 1) != '\0')
			start = end + 1;
		end = ft_strchr(start, ':');
		if (split_path(file, start, end, &flag))
			return (split_path(file, start, end, &flag));
	}
	return (NULL);
}
