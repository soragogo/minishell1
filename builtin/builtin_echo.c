/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:21:57 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 21:32:55 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_putstr(char *ch, int fd)
{
	if (!ch)
		return ;
	write(fd, ch, ft_strlen(ch));
}

int	handle_n_option(char **command, int *i)
{
	int		n_option;
	char	*ptr;

	n_option = 0;
	while (command[*i])
	{
		if (ft_strncmp(command[*i], "-n", 2) == 0)
		{
			ptr = command[*i] + 2;
			while (*ptr == 'n')
				ptr++;
			if (*ptr == '\0')
			{
				n_option = 1;
				(*i)++;
				continue ;
			}
		}
		break ;
	}
	return (n_option);
}

void	output_command(char **command, int start_idx, int status)
{
	int	i;

	i = start_idx;
	if (command[i] && !ft_strncmp(command[i], "-", 2))
		i++;
	while (command[i])
	{
		if (command[i] && ft_strncmp(command[i], "$?", 2) == 0)
			ft_putnbr_fd(status, STDOUT_FILENO);
		else
			ft_putstr(command[i], STDOUT_FILENO);
		i++;
		if (command[i])
			write(1, " ", STDOUT_FILENO);
	}
}

int	ft_echo(char **command, int status)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = handle_n_option(command, &i);
	output_command(command, i, status);
	if (n_option == 0)
		write(1, "\n", STDOUT_FILENO);
	return (0);
}
