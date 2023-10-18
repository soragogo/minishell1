/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_chdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:18:00 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 03:27:44 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	init_dir_path(char **home,
	char **pwd_path, char **old_path, t_env **env)
{
	*home = map_get(env, "HOME");
	if (!home)
	{
		error_message("cd", NULL, "HOME not set");
		return ;
	}
	*pwd_path = map_get(env, "PWD");
	if (!pwd_path)
	{
		error_message("cd", NULL, "PWD not set");
		return ;
	}
	*old_path = map_get(env, "OLDPWD");
	if (!old_path)
	{
		error_message("cd", NULL, "OLDPWD not set");
		return ;
	}
}

int	change_dir(char **commands, char *dir_path, char *old_path, t_env **env)
{
	if (chdir(dir_path) != 0)
	{
		set_env(env, ft_strdup("PWD"), ft_strdup(old_path), true);
		error_message("cd", commands[1], strerror(errno));
		free(dir_path);
		return (1);
	}
	return (0);
}

int	update_path(char **commands, t_env **env, char *pwd_path, char *dir_path)
{
	if (set_env(env, ft_strdup("OLDPWD"), ft_strdup(pwd_path), true) == -1
		|| set_env(env, ft_strdup("PWD"), ft_strdup(dir_path), true) == -1)
	{
		free(dir_path);
		return (1);
	}
	return (0);
}

int	create_dirpath(char **commands,
	char **dir_path, char *old_pwd, char *pwd_path)
{
	if (ft_strncmp(commands[1], "-", 2) == 0)
	{
		*dir_path = ft_strdup(old_pwd);
		if (!dir_path)
		{
			error_message("cd", NULL, "OLDPWD not set");
			return (1);
		}
	}
	else
	{
		if (commands[1][0] == '/')
			*dir_path = ft_strdup(commands[1]);
		else
			*dir_path = convert_relative_path(ft_strdup(pwd_path), commands[1]);
	}
	printf("dir_path: %s\n", *dir_path);
	return (0);
}

int	ft_chdir(char **commands, t_env **env)
{
	char	*home;
	char	*pwd_path;
	char	*old_pwd;
	char	*dir_path;

	dir_path = NULL;
	init_dir_path(&home, &pwd_path, &old_pwd, env);
	printf("dir_path: %s\n", dir_path);
	if (commands[1] == NULL)
		dir_path = ft_strdup(home);
	else if (ft_strncmp(commands[1], "~", 2) == 0)
		dir_path = ft_strjoin(home, commands[1] + 1);
	else if (create_dirpath(commands, &dir_path, old_pwd, pwd_path) == 1)
		return (1);
	if (change_dir(commands, dir_path, old_pwd, env) == 1)
		return (1);
	if (update_path(commands, env, pwd_path, dir_path) == 1)
		return (1);
	free(dir_path);
	return (0);
}
