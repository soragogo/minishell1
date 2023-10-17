#include "./../includes/minishell.h"

char *delete_path(char *dir_path)
{
	int i;
    char *ret;

    if(!dir_path)
        return (NULL);
	i = ft_strlen(dir_path);
	while (i > 2 && dir_path[i - 1] != '/')
		i--;
	if (i != 0){
        ret = malloc(sizeof(char) * i + 1);
        if (!ret)
            fatal_error("malloc error");
        ft_strlcpy(ret, dir_path, i);
    }
		// dir_path[i - 1] = '\0';
	else
    {
        ret = malloc(sizeof(char) * i + 1);
        if (!ret)
            fatal_error("malloc error");
        ft_strlcpy(ret, dir_path, i);
    }
		// dir_path[i] = '\0';
    // ret = ft_strdup(dir_path);
    free(dir_path);
    return (ret);
}

char *join_path(char *dir_path, char *input)
{
    char *tmp;

    tmp = ft_strjoin(dir_path, "/");
    free(dir_path);
    dir_path = ft_strjoin(tmp, input);
    free(tmp);
    return (dir_path);
}

void free_split(char **tmp)
{
    int i;

    i = 0;
    while (tmp[i])
    {
        free(tmp[i]);
        i++;
    }
    free(tmp);
}

char *convert_relative_path(char *dir_path, char *input)
{
    int i;
	char **tmp = ft_split(input, '/');
    char *ret;

    i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "..", 3) == 0)
		{
			dir_path = delete_path(dir_path);
            printf("dir_path: %s\n", dir_path);
		}
		else if (ft_strncmp(*tmp, ".", 2) == 0)
			;
		else
		{
            dir_path = join_path(dir_path, tmp[i]);
		}
		i++;
	}
    // ret = ft_strdup(*dir_path);
    printf("dir_path: %s\n", dir_path);
    free_split(tmp);
    return (dir_path);
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
}

int ft_chdir(char **commands, t_env **env)
{
	char *home;
    char *pwd_path;
	char *old_pwd = NULL;
	char *dir_path = NULL;

    init_dir_path(&home, &pwd_path, &old_pwd, env);
    printf("home: %s\n", home);
    printf("pwd_path: %s\n", pwd_path);
    printf("old_pwd: %s\n", old_pwd);
	if (commands[1] == NULL)//引数がない場合
        dir_path = ft_strdup(home);
	else if (ft_strncmp(commands[1], "~", 2) == 0)//引数が~の場合
	{
        dir_path = ft_strjoin(home, commands[1] + 1);
	}
	else if (ft_strncmp(commands[1], "-", 2) == 0)//引数が-の場合
	{
        dir_path = ft_strdup(old_pwd);
		if (!dir_path){
			error_message("cd", NULL, "OLDPWD not set");
			return (1);
		}
	}
	else//ディレクトリ直書きの場合
	{
		if (ft_strncmp(commands[1], "/", 2) == 0)//絶対パスの場合
            dir_path = ft_strdup(commands[1]);
		else
		{
			dir_path = convert_relative_path(ft_strdup(pwd_path), commands[1]);
		}
	}
	if (chdir(dir_path) != 0)
	{
		set_env(env, ft_strdup("PWD"), ft_strdup(old_pwd), true);
		error_message("cd", commands[1], strerror(errno));
		return (1);
	}
	if(set_env(env, ft_strdup("OLDPWD"), ft_strdup(pwd_path), true) == -1 || set_env(env, ft_strdup("PWD"), ft_strdup(dir_path), true) == -1)
	{
		free(dir_path);
		return (1);
	}
	ft_pwd();//確認用
    free(dir_path);
	return (0);
}
