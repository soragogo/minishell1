// #include "./../includes/minishell.h"

// char *delete_path(char *dir_path)
// {
// 	int i;
//     char *ret;

//     if(!dir_path)
//         return (NULL);
// 	i = ft_strlen(dir_path);
// 	while (i > 2 && dir_path[i - 1] != '/')
// 		i--;
// 	if (i != 0){
//         ret = malloc(sizeof(char) * i + 1);
//         if (!ret)
//             fatal_error("malloc error");
//         ft_strlcpy(ret, dir_path, i);
//     }
// 		// dir_path[i - 1] = '\0';
// 	else
//     {
//         ret = malloc(sizeof(char) * i + 1);
//         if (!ret)
//             fatal_error("malloc error");
//         ft_strlcpy(ret, dir_path, i);
//     }
// 		// dir_path[i] = '\0';
//     // ret = ft_strdup(dir_path);
//     free(dir_path);
//     return (ret);
// }

// char *join_path(char *dir_path, char *input)
// {
//     char *tmp;

//     tmp = ft_strjoin(dir_path, "/");
//     free(dir_path);
//     dir_path = ft_strjoin(tmp, input);
//     free(tmp);
//     return (dir_path);
// }

// char *convert_relative_path(char *dir_path, char *input)
// {
// 	char **tmp = ft_split(input, '/');
//     char *ret;

// 	while (*tmp)
// 	{
// 		if (ft_strncmp(*tmp, "..", 3) == 0)
// 		{
// 			dir_path = delete_path(dir_path);
//             printf("dir_path: %s\n", dir_path);
// 		}
// 		else if (ft_strncmp(*tmp, ".", 2) == 0)
// 			;
// 		else
// 		{
// 			// ft_strlcat(dir_path, "/", PATH_MAX);
// 			// ft_strlcat(dir_path, *tmp, PATH_MAX);
//             // dir_path = ft_strjoin(dir_path, "/");
//             // dir_path = ft_strjoin(dir_path, *tmp);
//             dir_path = join_path(dir_path, *tmp);
// 		}
// 		tmp++;
// 	}
//     // ret = ft_strdup(*dir_path);
//     printf("dir_path: %s\n", dir_path);
//     return (dir_path);
// }

// int main() {
//     //pwdを書き換える→setenv
//     //dir_pathを作る
//     char *dir_path = ft_strdup("/path/to/some/directory");
//     char *input = "../d/e/./f";
//     char *ret;

//     printf("Initial dir_path: %s\n", dir_path);

//     ret = convert_relative_path(dir_path, input);

//     // printf("Modified dir_path: %s\n", dir_path);

//     // dir_path = delete_path(dir_path);

//     // printf("After delete_path: %s\n", dir_path);

//     // dir_path のメモリを解放
//     // free(dir_path);
//     free(ret);

//     return 0;
// }
