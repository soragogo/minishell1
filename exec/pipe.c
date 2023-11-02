/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:25:47 by mayu              #+#    #+#             */
/*   Updated: 2023/11/02 19:01:48 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

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
		if (close(left_pipe[1]) == -1)
			fatal_error(strerror(errno));
		if (dup2(left_pipe[0], STDIN_FILENO) == -1)
			fatal_error(strerror(errno));
		if (close(left_pipe[0]) == -1)
			fatal_error(strerror(errno));
	}
	if (command->next)
	{
		if (close(right_pipe[0]) == -1)
			fatal_error(strerror(errno));
		if (dup2(right_pipe[1], STDOUT_FILENO) == -1)
			fatal_error(strerror(errno));
		if (close(right_pipe[1]) == -1)
			fatal_error(strerror(errno));
	}
}

int	wait_command(t_commandset *commands)
{
	int	status;

	while (commands)
	{
		if (waitpid(commands->pid, &status, 0) < 0)
			fatal_error("waitpid error");
		if (g_sigstatus == 1 || g_sigstatus == -1)
			g_sigstatus = 1;
		else if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sigstatus = WTERMSIG(status) + 128;
		commands = commands->next;
	}
	return (status);
}
