/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:50 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 20:06:23 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_pwd(t_info *info)
{
	char	*envp;

	envp = getcwd(NULL, 0);
	if (!envp)
	{
		envp = ft_strdup(map_get(&(info->map_head), "PWD"));
		if (!envp)
		{
			error_message("pwd", NULL, strerror(errno));
			return (1);
		}
	}
	write(STDOUT_FILENO, envp, ft_strlen(envp));
	write(STDOUT_FILENO, "\n", 1);
	free (envp);
	return (0);
}
