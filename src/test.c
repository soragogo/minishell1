// // #include "./../includes/minishell.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // char	*ft_strjoin(char const *s1, char const *s2)
// // {
// // 	char	*joined;
// // 	int		i;
// // 	int		strslen;

// // 	i = 0;
// // 	if (s1 == NULL || s2 == NULL)
// // 		return (NULL);
// // 	strslen = strlen(s1) + strlen(s2);
// // 	joined = (char *)malloc(sizeof(char) * (strslen + 1));
// // 	if (joined == NULL)
// // 		return (NULL);
// // 	while (*s1)
// // 		joined[i++] = *s1++;
// // 	while (*s2)
// // 		joined[i++] = *s2++;
// // 	joined[i] = 0;
// // 	return (joined);
// // }


// // void env_join(char *name, char *value, char **environ)
// // {
// // 	*environ = ft_strjoin(name, "=");
// // 	*environ = ft_strjoin(*environ, value);
// // }

// // char **create_environ(t_env **env_head)
// // {
// // 	t_env *tmp;
// // 	char **environ;
// //     // char **ret;
// //     int i;

// //     // ret = environ;
// //     i = 0;
// // 	tmp = *env_head;
// // 	while (tmp)
// // 	{
// // 		// printf("%s=%s\n", tmp->name, tmp->value);
// // 		env_join(tmp->name, tmp->value, &environ[i]);
// // 		i++;
// // 		tmp = tmp->next;
// // 	}
// //     environ[i] = NULL;
// // 	return (environ);
// // }

// // int main() {
// //     // 仮想的な環境変数リストを作成します
// //     t_env *env1 = (t_env *)malloc(sizeof(t_env));
// //     env1->name = "PATH";
// //     env1->value = "/usr/bin:/bin";
// //     env1->next = NULL;

// //     t_env *env2 = (t_env *)malloc(sizeof(t_env));
// //     env2->name = "HOME";
// //     env2->value = "/user/home";
// //     env2->next = NULL;

// //     // 環境変数リストを連結します
// //     env1->next = env2;

// //     // create_environ 関数を呼び出して environ 形式の文字列配列を作成します
// //     char **environ = create_environ(&env1);

// //     // environ の内容を表示します
// //     for (int i = 0; environ[i] != NULL; i++) {
// //         printf("%s\n", environ[i]);
// //     }

// //     // メモリの解放を行います
// //     // この部分のメモリ管理は実際のプログラムに合わせて適切に行ってください
// //     for (int i = 0; environ[i] != NULL; i++) {
// //         free(environ[i]);
// //     }
// //     // free(environ);
    
// //     // // ダミー環境変数リストのメモリ解放
// //     // free(env1);
// //     // free(env2);

// //     return 0;
// // }



// #include "../includes/minishell.h"

// // void fatal_error(const char *msg) __attribute__((noreturn));

// void fatal_error(char *msg)
// {
// 	printf("%s\n", msg);
// 	exit(1);
// }

// int ft_system(t_token *tokens, int *status)
// {
// 	pid_t pid;
// 	//char *commands[] = {"bash", "-c", command, NULL};
// 	//	char *commands[] = {"/bin/bash", "-c", "cat <<a", NULL};
// 	extern char **environ;

// 	pid = fork();
// 	char *token_twod[10000];
// 	int i = 0;

// 	search_path(tokens);
// 	while (tokens[i].arg != NULL)
// 	{
// 		token_twod[i] = tokens[i].arg;
// 		i++;
// 	}
// 	token_twod[i] = NULL;
// //	for (int i = 0; token_twod[i] != NULL; i++)
// //		printf("token_twod[%d]: [%s]\n",i,  token_twod[i]);

// 	if (pid < 0)
// 		fatal_error("fork");
// 	if (pid == 0)
// 	{
// 		execve(token_twod[0], token_twod, environ);
// 		fatal_error("minishell");
// 	}
// 	else if (pid > 0)
// 	{
// 		do
// 		{
// 			if (waitpid(pid, status, 0) == -1)
// 			{
// 				return -1;
// 			}
// 		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
// 		*status = WEXITSTATUS(*status);
// 	}
// 	else
// 		return (-1);
// 	return WIFEXITED(*status);
// }

// #include <libc.h>
// #include "../includes/minishell.h"

// char *fetch_path(char *file)
// {
// 	char path[PATH_MAX];
// 	char *pathlist = getenv("PATH");
// 	//printf("pathlist: [%s]\n", pathlist);

// 	char *start = pathlist;
// 	char *end = NULL;
// 	// char *tmp;
// 	char *result;
// 	int flag = 0;
// 	while (flag == 0)
// 	{
// 		bzero(path, PATH_MAX);
// 		if (end != NULL && *(end + 1)!='\0')
// 			start = end + 1;
// 		end = ft_strchr(start, ':');
// 		if (end)
// 		{
// 			strlcpy(path, start, end - start + 1);
// 		}
// 		else
// 		{
// 			flag = 1;
// 			strcpy(path, start);
// 		}
// 		strlcat(path, "/", PATH_MAX);
// 		strlcat(path, file, PATH_MAX);

// 	if (access(path, F_OK) == 0)
// 	{
// //		printf("path: [%s]\n",path);
// 		result = ft_strdup(path);
// 		return (result);
// 	}
// 	}
// 	return (NULL);
// }

// t_token *search_path(t_token *tokens)
// {
// 	t_token *tmp_tokens = tokens;
// 	char *tmp;
// 	for (int i = 0; tmp_tokens[i].arg != NULL; i++)
// 	{
// 		tmp = fetch_path(tmp_tokens[i].arg);
// 		if (tmp != NULL)
// 		{
// 			free(tmp_tokens[i].arg);
// 			tmp_tokens[i].arg = tmp;
// 		}
// 	}
// 	return (tmp_tokens);
// }

// // #include "../includes/minishell.h"
// // #include <unistd.h>
// // int main()
// // {
// // 	char *command_buf;
// // 	while (1)
// // 	{
// // 		command_buf = readline("exec_path> ");
// // 		search_path(command_buf);
// // 		printf("%s\n", command_buf);
// // 		if (command_buf != NULL)
// // 			exec(command_buf);
// // 		free(command_buf);
// // 	}	return (0);
// // }