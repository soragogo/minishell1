/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:14:59 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 16:15:27 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*delete_path(char *dir_path)
{
	int		i;
	char	*ret;

	if (!dir_path)
		return (NULL);
	i = ft_strlen(dir_path);
	while (i > 2 && dir_path[i - 1] != '/')
		i--;
	if (i != 0)
	{
		ret = malloc(sizeof(char) * i + 1);
		if (!ret)
			fatal_error("malloc error");
		ft_strlcpy(ret, dir_path, i);
	}
	free(dir_path);
	return (ret);
}

char	*join_path(char *dir_path, char *input)
{
	char	*tmp;

	tmp = ft_strjoin(dir_path, "/");
	free(dir_path);
	dir_path = ft_strjoin(tmp, input);
	free(tmp);
	return (dir_path);
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

char	*convert_relative_path(char *dir_path, char *input)
{
	int		i;
	char	**tmp;
	char	*ret;

	i = 0;
	tmp = ft_split(input, '/');
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "..", 3) == 0)
			dir_path = delete_path(dir_path);
		else if (ft_strncmp(*tmp, ".", 2) == 0)
			;
		else
			dir_path = join_path(dir_path, tmp[i]);
		i++;
	}
	free_split(tmp);
	return (dir_path);
}
