/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:33:24 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 17:11:07 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

void	free_before_closing(t_commandset *command, char *command_buf)
{
	free_commandset(command);
	free(command_buf);
}

bool	only_space(char *command)
{
	while (*command)
	{
		if (*command != ' ' && *command != '\t')
			return (false);
		command++;
	}
	return (true);
}

char	*ft_readline(void)
{
	char	*command_buf;

	command_buf = readline("minishell> ");
	if (command_buf)
		add_history(command_buf);
	return (command_buf);
}
