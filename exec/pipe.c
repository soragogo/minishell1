/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:25:47 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 13:27:38 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

void	create_pipe(t_commandset *command, int new_pipe[2])
{
	if (command->next)
	{
		if (pipe(new_pipe) < 0)
			fatal_error("pipe error");
	}
}

void	handle_pipe(int left_pipe[2], int right_pipe[2], t_commandset *command)
{
	if (command->prev)
	{
		close(left_pipe[1]);
		dup2(left_pipe[0], STDIN_FILENO);
		close(left_pipe[0]);
	}
	if (command->next)
	{
		close(right_pipe[0]);
		dup2(right_pipe[1], STDOUT_FILENO);
		close(right_pipe[1]);
	}
}

int	wait_command(t_commandset *commands, t_info *info)
{
	int	status;

	while (commands)
	{
		if (waitpid(commands->pid, &status, 0) < 0)
			fatal_error("waitpid error");
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
		commands = commands->next;
	}
	return (status);
}
