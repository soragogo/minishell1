/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:29:04 by mayu              #+#    #+#             */
/*   Updated: 2023/10/28 19:13:54 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser.h"

void	check_isdir(char **command)
{
	struct stat	*buf;

	buf = NULL;
	if (ft_strncmp(command[0], "./", 2) == 0)
	{
		if (stat (command[0], buf) != 0 && access (command[0], F_OK) != 0)
			missing_file_error(command[0]);
		else
			error_message(command[0], NULL, "Permission denied");
		exit (126);
	}
	else if (command[0][0] == '/')
	{
		if (stat (command[0], buf) != 0 && access (command[0], F_OK) != 0)
			missing_file_error(command[0]);
		else
			error_message(command[0], NULL, "is a directory");
		exit (126);
	}
	error_message(command[0], NULL, "command not found");
	exit(127);
}

int	child_prosess(t_commandset *commands, t_info *info)
{
	char	*path;
	char	**my_environ;
	int		status;

	my_environ = create_environ(&(info->map_head));
	if (is_builtin(commands) != -1)
	{
		status = exec_builtin(commands, info);
		exit(status);
	}
	else
	{
		handle_redirection(commands, info);
		status = execve(*commands->command, commands->command, my_environ);
		path = fetch_path(*commands->command, &(info->map_head));
		status = execve(path, commands->command, my_environ);
		free(path);
		if (status == -1)
			check_isdir(commands->command);
	}
	free_environ(my_environ);
	return (status);
}

void	update_pipe(t_commandset *commands, int new_pipe[2], int old_pipe[2])
{
	if (commands->prev)
	{
		if (close(old_pipe[0]) == -1)
			fatal_error(strerror(errno));
		if (close(old_pipe[1]) == -1)
			fatal_error(strerror(errno));
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
			if (commands->command == NULL)
				break ;
			exec_command(commands, info);
			commands = commands->next;
		}
		status = wait_command(tmp_head);
	}
	return (status);
}
