/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:37:58 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 15:38:20 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include "../includes/minishell.h"

char	*fetch_path(char *file, t_env **map)
{
	char	path[PATH_MAX];
	char	*pathlist;
	char	*start;
	char	*end;
	char	*result;
	int		flag;
	int		len;

	flag = 0;
	end = NULL;
	pathlist = map_get(map, "PATH");
	if (pathlist == NULL)
		return (NULL);
	start = pathlist;
	end = NULL;
	while (flag == 0)
	{
		ft_bzero(path, PATH_MAX);
		if (end != NULL && *(end + 1) != '\0')
			start = end + 1;
		end = ft_strchr(start, ':');
		if (end)
			ft_strlcpy(path, start, end - start + 1);
		else
		{
			flag = 1;
			len = ft_strlen(start);
			ft_strlcpy(path, start, len + 1);
		}
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, file, PATH_MAX);
		if (access(path, F_OK) == 0)
		{
			result = ft_strdup(path);
			return (result);
		}
	}
	return (NULL);
}
