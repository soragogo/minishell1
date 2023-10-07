#include <libc.h>
#include "../includes/minishell.h"

char *fetch_path(char *file, t_env **map)
{
	char path[PATH_MAX];
	// char *pathlist = getenv("PATH");
	char *pathlist;
	char *start;
	char *end = NULL;
	char *result;
	int flag = 0;

	
	// while (*map)
	// {
	// 	printf("name: %s\nvalue: %s\n", (*map)->name, (*map)->value);
	// 	map = (*map)->next;
	// }
	pathlist = map_get(map, "PATH");
	// printf("pathlist: [%s]\n", pathlist);
	if (pathlist == NULL)
		return (NULL);
	start = pathlist;
	end = NULL;
	// printf("pathlist: [%s]\n", pathlist);
	while (flag == 0)
	{
		bzero(path, PATH_MAX);
		if (end != NULL && *(end + 1)!='\0')
			start = end + 1;
		end = ft_strchr(start, ':');
		if (end)
		{
			strlcpy(path, start, end - start + 1);
		}
		else
		{
			flag = 1;
			strcpy(path, start);
		}
		strlcat(path, "/", PATH_MAX);
		strlcat(path, file, PATH_MAX);
		// printf("file: [%s]\n",file);
		// printf("path: [%s]\n",path);
		if (access(path, F_OK) == 0)
		{
			
			result = ft_strdup(path);
			return (result);
		}
	}
	return (NULL);
}

char *search_path(char *command)
{
	// t_token *tmp_tokens = tokens;

	// char **tmp = &command;
	char *ret;
	// for (int i = 0; tmp_tokens[i].arg != NULL; i++)
	// for (int i = 0; tmp[i] != NULL; i++)
	// {
		// ret = fetch_path(command);
		// if (tmp != NULL)
		// {
		// 	// free(tmp_tokens[i].arg);
		// 	ret = tmp[i];
		// }
	// }
	return (ret);
}


// int main() {
// 	t_env *map;
// 	map = map_new();
//     envmap_init(&map);
//     char *command = "wc"; // 実行したいコマンド名を設定
//     char *path = fetch_path(command, &map);

// 	t_info info;
// 	info.map_head = map;
//     if (path) {
//         printf("コマンド '%s' のフルパス: %s\n", command, path);
//         // ここで path を使ってコマンドを実行できます
//     } else {
//         printf("コマンド '%s' が見つかりませんでした。\n", command);
//     }

//     return 0;
// }

// #include "../includes/minishell.h"
// #include <unistd.h>
// int main()
// {
// 	char *command_buf;
// 	while (1)
// 	{
// 		command_buf = readline("exec_path> ");
// 		search_path(command_buf);
// 		printf("%s\n", command_buf);
// 		if (command_buf != NULL)
// 			exec(command_buf);
// 		free(command_buf);
// 	}	return (0);
// }
