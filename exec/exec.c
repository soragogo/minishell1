/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:29:04 by mayu              #+#    #+#             */
/*   Updated: 2023/10/18 15:32:11 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

int	is_builtin(t_commandset *command)
{
	static char	*builtin[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int			i;

	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strcmp(*command[0].command, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(t_commandset *commands, t_info *info)
{
	int	status;
	int	dupinfd;
	int	dupoutfd;

	status = 0;
	handle_redirection(commands, info);
	if (ft_strncmp(*commands[0].command, "echo", 4) == 0)
		status = ft_echo(commands->command, info->exit_status_log);
	else if (ft_strncmp(*commands[0].command, "cd", 3) == 0)
		status = ft_chdir(commands->command, &(info->map_head));
	else if (ft_strncmp(*commands[0].command, "env", 4) == 0)
		status = ft_env(&(info->map_head));
	else if (ft_strncmp(*commands[0].command, "pwd", 4) == 0)
		status = ft_pwd();
	else if (ft_strncmp(*commands[0].command, "export", 7) == 0)
		status = ft_export(&info->map_head, commands->command);
	else if (ft_strncmp(*commands[0].command, "unset", 6) == 0)
		status = ft_unset(&info->map_head, commands->command);
	else if (ft_strncmp(*commands[0].command, "exit", 5) == 0)
		status = ft_exit(commands->command, info);
	else
		return (-1);
	undo_redirect(commands->node);
	return (status);
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

void	create_pipe(t_commandset *command, int new_pipe[2])
{
	if (command->next)
	{
		if (pipe(new_pipe) < 0)
			fatal_error("pipe error");
	}
}

int	exec_command(t_commandset *commands, t_info *info)
{
	int			status;
	static int	new_pipe[2];
	static int	old_pipe[2];
	char		*path;
	char		**my_environ;
	pid_t		pid;

	status = 0;
	create_pipe(commands, new_pipe);
	my_environ = create_environ(&(info->map_head));
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		handle_pipe(old_pipe, new_pipe, commands);
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
	}
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
	commands->pid = pid;
	free_environ(my_environ);
	return (status);
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

int	handle_command(t_commandset *commands, t_info *info)
{
	t_commandset	*tmp_head;
	int				status;
	int				i;

	i = 0;
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
		status = wait_command(tmp_head, info);
	}
	return (status);
}
