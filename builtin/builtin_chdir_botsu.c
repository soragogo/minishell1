// #include "./../includes/minishell.h"

// void delete_path(char *dir_path)
// {
// 	int i;

// 	i = ft_strlen(dir_path);
// 	while (i > 2 && dir_path[i - 1] != '/')
// 		i--;
// 	if (i != 0)
// 		dir_path[i - 1] = '\0';
// 	else
// 		dir_path[i] = '\0';
// }

// void convert_relative_path(char **dir_path, char *input)
// {
// 	char **tmp = ft_split(input, '/');

// 	while (*tmp)
// 	{
// 		if (ft_strncmp(*tmp, "..", 3) == 0)
// 		{
// 			delete_path(*dir_path);
// 		}
// 		else if (ft_strncmp(*tmp, ".", 2) == 0)
// 			;
// 		else
// 		{
// 			ft_strlcat(*dir_path, "/", PATH_MAX);
// 			ft_strlcat(*dir_path, *tmp, PATH_MAX);
// 		}
// 		tmp++;
// 	}
// }

// int init_dir_path(char **home, char **dir_path, char **old_pwd, t_env **env){
// 	*home = map_get(env, "HOME");
// 	if (!home){
// 		error_message("cd", NULL, "HOME not set");
// 		return (1);
// 	}
// 	*dir_path = map_get(env, "PWD");
// 	if (!dir_path){
// 		error_message("cd", NULL, "PWD not set");
// 		return (1);
// 	}
// 	*old_pwd = calloc(sizeof(char) * PATH_MAX, 1);
// 	if (!old_pwd){
// 		fatal_error("calloc error");
// 	}
// 	ft_strlcpy(*old_pwd, *dir_path, PATH_MAX);
// 	// *old_pwd = ft_strdup(*dir_path);
// 	return (0);
// }

// int exec_chdir(char *dir_path, char *old_pwd, t_env **env, char **commands){
// 	if (chdir(dir_path) != 0)
// 	{
// 		set_env(env, "PWD", old_pwd, false);
// 		error_message("cd", commands[1], strerror(errno));
// 		free(old_pwd);
// 		free(dir_path);
// 		return (1);
// 	}
// 	if(set_env(env, "OLDPWD", old_pwd, false) == -1 || set_env(env, "PWD", dir_path, false) == -1)
// 	{
// 		free(old_pwd);
// 		return (1);
// 	}
// 	return (0);
// }

// int ft_chdir(char **commands, t_env **env)
// {
// 	char *home;
// 	char *dir_path;
// 	char *old_pwd;
// 	char *pwd_path;

// 	if (init_dir_path(&home, &pwd_path, &old_pwd, env) == 1)
// 		return (1);
// 	printf("home:%s\n", home);
// 	printf("pwd_path:%s\n", pwd_path);
// 	printf("old_pwd:%s\n", old_pwd);
// 	if (commands[1] == NULL)//引数がない場合
// 	{
// 		// ft_strlcpy(dir_path, home, PATH_MAX);
// 		dir_path = home;
// 		if(exec_chdir(dir_path, old_pwd, env, commands) == 1)
// 			return (1);
// 	}
// 	else if (ft_strncmp(commands[1], "~", 2) == 0)//引数が~の場合
// 	{
// 		// ft_strlcpy(dir_path, home, PATH_MAX);
// 		// ft_strlcat(dir_path, commands[1] + 1, PATH_MAX);
// 		dir_path = home;
// 		ft_strlcat(dir_path, commands[1] + 1, PATH_MAX);
// 		if(exec_chdir(dir_path, old_pwd, env, commands) == 1)
// 			return (1);
// 		// printf("dir_path:%s\n", dir_path);
// 	}
// /* -----------------------------ここまでできてる------------------------------- */
// 	else if (ft_strncmp(commands[1], "-", 2) == 0)//引数が-の場合
// 	{
// 		dir_path = map_get(env, "OLDPWD");
// 		if (!dir_path){
// 			error_message("cd", NULL, "OLDPWD not set");
// 			return (1);
// 		}
// 		if(exec_chdir(dir_path, old_pwd, env, commands) == 1)
// 			return (1);
// 		free(dir_path);
// 	}
// 	else//ディレクトリ直書きの場合
// 	{
// 		if (ft_strncmp(commands[1], "/", 2) == 0)//絶対パスの場合
// 		{
// 			printf("1\n");
// 			// ft_strlcpy(dir_path, commands[1], PATH_MAX);
// 			dir_path = commands[1];
// 			if(exec_chdir(dir_path, old_pwd, env, commands) == 1)
// 				return (1);
// 		}
// 		else
// 		{
// 			dir_path = ft_strdup(pwd_path);
// 			// ft_strlcpy(dir_path, pwd_path, PATH_MAX);
// 			convert_relative_path(&dir_path, commands[1]);
// 			if(exec_chdir(dir_path, old_pwd, env, commands) == 1)
// 				return (1);
// 			free(dir_path);
// 		}
// 	}
// 	printf("2\n");
// 	ft_pwd();//確認用
// 	free(pwd_path);
// 	free(old_pwd);
// 	free(home);
// 	return (0);
// }
