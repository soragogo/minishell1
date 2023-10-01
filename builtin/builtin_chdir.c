#include "./../includes/minishell.h"

void delete_path(char *dir_path){
	int i;

	i = ft_strlen(dir_path);
	while (dir_path[i - 1] != '/' && i > 2)
		i--;
	if (i != 0)
		dir_path[i - 1] = '\0';
	else
		dir_path[i] = '\0';
}

void convert_relative_path(char **dir_path, char *input){
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
			strlcat(*dir_path, "/", PATH_MAX);
			strlcat(*dir_path, *tmp, PATH_MAX);
		}
		tmp++;
	}
}

int ft_chdir(char **commands, t_env **env)
{
	char *home;
	char *dir_path;
	char *old_pwd;

	home = getenv("HOME");
	if (!home){
		printf("HOME not set");
		return (1);
	}
	dir_path = map_get(env, "PWD");
	if (!dir_path){
		printf("PWD not set");
		return (1);
	}
	old_pwd = calloc(sizeof(char) * PATH_MAX, 1);
	strlcpy(old_pwd, dir_path, PATH_MAX);
	if (commands[1] == NULL)//引数がない場合
		strlcpy(dir_path, home, PATH_MAX);
	// else if (commands[1][0] == '~' && strlen(commands[1]) == 1)//引数が~の場合 ２文字の場合弾けるようにstrcmpに変更
	else if (strcmp(commands[1], "~") == 0)//引数が~の場合
	{
		strlcpy(dir_path, home, PATH_MAX);//
		strlcat(dir_path, commands[1] + 1, PATH_MAX);//
	}
	// else if (commands[1] == '-')//引数が-の場合
	else if (strcmp(commands[1], "-") == 0)//引数が-の場合
	{
		dir_path = map_get(env, "OLDPWD");
		if (!dir_path){
			printf("OLDPWD not set");
			return (1);
		}
		printf("%s\n", dir_path);
	}
	else//ディレクトリ直書きの場合
	{
		// if (commands[1] == '/')//絶対パスの場合
		if (strcmp(commands[1], "/") == 0)//絶対パスの場合
			strlcpy(dir_path, commands[1], PATH_MAX);
		else
		{
			convert_relative_path(&dir_path, commands[1]);
		}
	}
	if (chdir(dir_path) != 0)
	{
		set_env(env, "PWD", old_pwd);
		printf("cd: no such file or directory: %s\n", dir_path);
		return (1);
	}
	// int ret = chdir(dir_path);
	// printf("ret: %d\n", ret);
	set_env(env, "OLDPWD", old_pwd);
	set_env(env, "PWD", dir_path);
	// printf("OLDPWD: %s\n\n", map_get(env, "OLDPWD"));
	printf("PWD: %s\n", map_get(env, "PWD"));
	// printf("%s\n", dir_path);
	// chdir(dir_path);
	ft_pwd();
	free(old_pwd);
	return (0);
}
