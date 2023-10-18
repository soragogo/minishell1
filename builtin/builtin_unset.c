/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:25:11 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 15:25:12 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_unset(t_env **env_head, char **commands)
{
	int	i;

	i = 1;
	while (commands[i] != NULL)
	{
		env_unset(env_head, commands[i]);
		i++;
	}
	return (0);
}
