/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:24:50 by mayu              #+#    #+#             */
/*   Updated: 2023/10/28 15:14:33 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_pwd(t_info *info)
{
	char	*envp;

	envp = ft_strdup(map_get(&(info->map_head), "PWD"));
	if (!envp)
	{
		envp = getcwd(NULL, 0);
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
