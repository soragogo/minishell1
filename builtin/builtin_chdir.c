#include "./../includes/minishell.h"

void delete_path(char *dir_path)
{
	int i;

	i = ft_strlen(dir_path);
	while (i > 2 && dir_path[i - 1] != '/')
		i--;
	if (i != 0)
		dir_path[i - 1] = '\0';
	else
		dir_path[i] = '\0';
}

void convert_relative_path(char **dir_path, char *input)
{
	char **tmp = ft_split(input, '/');

	while (*tmp)
	{
		if (ft_strncmp(*tmp, "..", 3) == 0)
		{
			delete_path(*dir_path);
		}
		else if (ft_strncmp(*tmp, ".", 2) == 0)
			;
		else
		{
			ft_strlcat(*dir_path, "/", PATH_MAX);
			ft_strlcat(*dir_path, *tmp, PATH_MAX);
		}
		tmp++;
	}
}

void init_dir_path(char **home, char **pwd_path, char **old_path, t_env **env){
    *home = map_get(env, "HOME");
    if (!home){
        error_message("cd", NULL, "HOME not set");
        return ;
    }
    *pwd_path = map_get(env, "PWD");
    if (!pwd_path){
        error_message("cd", NULL, "PWD not set");
        return ;
    }
    *old_path = map_get(env, "OLDPWD");
    if (!old_path){
        error_message("cd", NULL, "OLDPWD not set");
        return ;
    }
    ft_strlcpy(*old_path, *pwd_path, PATH_MAX);
}

int ft_chdir(char **commands, t_env **env)
{
	char *home;
    char *pwd_path;
	char *old_pwd = NULL;
	char *dir_path = NULL;
	// home = getenv("HOME");
	// if (!home){
	// 	error_message("cd", NULL, "HOME not set");
	// 	return (1);
	// }
	// dir_path = map_get(env, "PWD");
	// if (!dir_path){
	// 	error_message("cd", NULL, "PWD not set");
	// 	return (1);
	// }
	// old_pwd = calloc(sizeof(char) * PATH_MAX, 1);
	// if (!old_pwd){
	// 	fatal_error("calloc error");
	// }
	// ft_strlcpy(old_pwd, dir_path, PATH_MAX);
    init_dir_path(&home, &pwd_path, &old_pwd, env);
    printf("home: %s\n", home);
    printf("pwd_path: %s\n", pwd_path);
    printf("old_pwd: %s\n", old_pwd);

/* ------------------------------------------------------------- */
	if (commands[1] == NULL)//引数がない場合
		// ft_strlcpy(dir_path, home, PATH_MAX);
        dir_path = ft_strdup(home);
	else if (ft_strncmp(commands[1], "~", 2) == 0)//引数が~の場合
	{
		ft_strlcpy(dir_path, home, PATH_MAX);
		ft_strlcat(dir_path, commands[1] + 1, PATH_MAX);
	}
	// else if (commands[1] == '-')//引数が-の場合
	else if (ft_strncmp(commands[1], "-", 2) == 0)//引数が-の場合
	{
		dir_path = map_get(env, "OLDPWD");
		if (!dir_path){
			error_message("cd", NULL, "OLDPWD not set");
			return (1);
		}
		// printf("%s\n", dir_path);
	}
	else//ディレクトリ直書きの場合
	{
		if (ft_strncmp(commands[1], "/", 2) == 0)//絶対パスの場合
			ft_strlcpy(dir_path, commands[1], PATH_MAX);
		else
		{
			convert_relative_path(&dir_path, commands[1]);
		}
	}
	if (chdir(dir_path) != 0)
	{
		set_env(env, "PWD", old_pwd, false);
		error_message("cd", commands[1], strerror(errno));
		return (1);
	}
	if(set_env(env, "OLDPWD", old_pwd, false) == -1 || set_env(env, "PWD", dir_path, false) == -1)
	{
		free(old_pwd);
		return (1);
	}
    // printf("dirpath_pointer2: %p\n", dir_path);
    // printf("oldpwd_pointer2: %p\n", old_pwd);
	// printf("OLDPWD: %s\n\n", map_get(env, "OLDPWD"));
	// printf("PWD: %s\n", map_get(env, "PWD"));
	// printf("%s\n", dir_path);
	ft_pwd();//確認用
	free(old_pwd);
    // free(dir_path);
    // free(home);
    // free(pwd_path);
	return (0);
}
