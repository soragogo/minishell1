/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:25:47 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 12:30:50 by mayu             ###   ########.fr       */
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

void	handle_pipe(int left_pipe[2], int right_pipe[2], t_commandset *command, t_info *info)
{
	if (command->prev && info->exit_status_log == 0)
	{
		if (close(left_pipe[1]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(left_pipe[1]), strerror(errno));
		if (command->node && (command->node->type == HERE_DOCUMENT || command->node->type == REDIRECT_IN))// || command->node->type == REDIRECT_IN
		{
			if (close(left_pipe[0]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(left_pipe[0]), strerror(errno));
			return ;
		}
		if (dup2(left_pipe[0], STDIN_FILENO) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(left_pipe[0]), strerror(errno));
		if (close(left_pipe[0]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(left_pipe[0]), strerror(errno));
	}
	if (command->next)
	{
		if (close(right_pipe[0]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(right_pipe[0]), strerror(errno));
		if (command->node && (command->node->type == REDIRECT_OUT || command->node->type == APPEND_OUT))
		{
			if (close(right_pipe[1]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(right_pipe[1]), strerror(errno));
			return ;
		}
		if (dup2(right_pipe[1], STDOUT_FILENO) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(right_pipe[1]), strerror(errno));
		if (close(right_pipe[1]) == -1)
			// fatal_error(strerror(errno));
			error_message(NULL, ft_itoa(right_pipe[1]), strerror(errno));
	}
}

int	wait_command(t_commandset *commands)
{
	int	status;

	while (commands)
	{
		if (commands->pid == -1)
		{
			commands = commands->next;
			continue ;
		}
		if (waitpid(commands->pid, &status, 0) < 0)
			// fatal_error("waitpid error");
			error_message(NULL, NULL, strerror(errno));
		if (g_sigstatus == 1 || g_sigstatus == -1)
			g_sigstatus = 1;
		else if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sigstatus = WTERMSIG(status) + 128;
		commands = commands->next;
	}
	if (status > 255)
		status = status % 256 + 1;
	return (status);
}
