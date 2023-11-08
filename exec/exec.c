/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:29:04 by mayu              #+#    #+#             */
/*   Updated: 2023/11/08 18:17:25 by mayu             ###   ########.fr       */
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
	else if (command[0][0] == '/' ||
		command[0][ft_strlen(command[0]) - 1] == '/')
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

void	handle_heredocument(t_commandset *commands, t_info *info)
{
	t_redirect	*tmp_node;

	tmp_node = commands->node;
	while (tmp_node)
	{
		if (tmp_node->type == HERE_DOCUMENT)
			here_document(tmp_node, info);
		tmp_node = tmp_node->next;
	}
	tmp_node = commands->node;
}

int	exec_command(t_commandset *commands, t_info *info)
{
	int			status;
	static int	new_pipe[2];
	static int	old_pipe[2];
	pid_t		pid;

	status = 0;
	if (handle_redirection(commands, info) == 1)
	{
		set_err_status(commands, info);
		return (1);
	}
	create_pipe(commands, new_pipe);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		handle_pipe(old_pipe, new_pipe, commands, info);
		status = child_prosess(commands, info);
	}
	update_pipe(commands, new_pipe, old_pipe, info);
	undo_redirect(commands->node, 0);
	commands->pid = pid;
	return (status);
}

void	handle_command(t_commandset *commands, t_info *info)
{
	t_commandset	*tmp_head;

	tmp_head = commands;
	if (!(commands->next) && is_builtin(commands) != -1)
		info->exit_status_log = exec_builtin(commands, info);
	else
	{
		while (commands != NULL)
		{
			if (commands->command == NULL)
				break ;
			if (exec_command(commands, info) == -1)
				return ;
			commands = commands->next;
		}
		if (info->exit_status_log == -1)
		{
			wait_command(tmp_head);
			info->exit_status_log = 1;
		}
		else
			info->exit_status_log = wait_command(tmp_head);
		info->file_err = 0;
	}
}
