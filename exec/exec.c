/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:29:04 by mayu              #+#    #+#             */
/*   Updated: 2023/10/20 17:02:58 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

int	child_prosess(t_commandset *commands, t_info *info)
{
	char	*path;
	char	**my_environ;
	int		status;

	status = 0;
	my_environ = create_environ(&(info->map_head));
	if (is_builtin(commands) != -1)
	{
		status = exec_builtin(commands, info);
		exit(status);
	}
	else
	{
		handle_redirection(commands, info);
		path = fetch_path(*commands->command, &(info->map_head));
		status = execve(path, commands->command, my_environ);
		free(path);
		if (status == -1)
		{
			error_message(*commands->command, NULL, "command not found");
			exit(127);
		}
	}
	free_environ(my_environ);
	return (status);
}

void	update_pipe(t_commandset *commands, int new_pipe[2], int old_pipe[2])
{
	if (commands->prev)
	{
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	if (commands->next)
	{
		old_pipe[0] = new_pipe[0];
		old_pipe[1] = new_pipe[1];
	}
}

int	exec_command(t_commandset *commands, t_info *info)
{
	int			status;
	static int	new_pipe[2];
	static int	old_pipe[2];
	pid_t		pid;

	status = 0;
	create_pipe(commands, new_pipe);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		handle_pipe(old_pipe, new_pipe, commands);
		status = child_prosess(commands, info);
	}
	update_pipe(commands, new_pipe, old_pipe);
	commands->pid = pid;
	return (status);
}

int	handle_command(t_commandset *commands, t_info *info)
{
	t_commandset	*tmp_head;
	int				status;

	status = 0;
	tmp_head = commands;
	if (!(commands->next) && is_builtin(commands) != -1)
		status = exec_builtin(commands, info);
	else
	{
		while (commands != NULL)
		{
			exec_command(commands, info);
			commands = commands->next;
		}
		status = wait_command(tmp_head);
	}
	return (status);
}
