#include "../includes/minishell.h"

// int	skip_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	return (i);
// }

int	skip_space(char **str)
{
	int	i;
	char *tmp;

	i = 0;
	tmp = *str;
	while ((9 <= tmp[i] && tmp[i] <= 13) || tmp[i] == 32)
		i++;
	*str = &tmp[i];
	return (i);
}

char **join(char const *s1, char const *s2, char **environ)
{
	int		i;
	int		strslen;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	strslen = ft_strlen(s1) + ft_strlen(s2);
	environ = (char **)malloc(sizeof(char *) * 1);
	*environ = (char *)malloc(sizeof(char) * (strslen + 1));
	if (environ == NULL)
		return (NULL);
	while (*s1)
		environ[0][i++] = *s1++;
	while (*s2)
		environ[0][i++] = *s2++;
	environ[0][i] = 0;
	return (environ);
}

char  *env_join(char *name, char *value, char **environ)
{
	environ = join(name, "=", environ);
	environ = join(environ[0], value, environ);
	return (environ[0]);
}

//KEY=valueの形で環境変数を作成する関数
char **create_environ(t_env **env_head)
{
	t_env *tmp;
	char **environ;
    int i;

    i = 0;
	tmp = *env_head;
	environ = (char **)malloc(sizeof(char *) * 1);
	while (tmp)
	{
		environ[i] = (char *)malloc(sizeof(char *) * 1);
		environ[i] = env_join(tmp->name, tmp->value, &environ[i]);
		i++;
		tmp = tmp->next;
	}
	environ[i] = (char *)malloc(sizeof(char *) * 1);
    environ[i] = NULL;
	return (environ);
}

/* -------------------------------------------------------------- */



// // テスト用のフェイク環境変数リストを作成する関数
// t_env *create_fake_envlist()
// {
//     t_env *env_list = NULL;

//     set_env(&env_list, "VAR1", "value1");
//     set_env(&env_list, "VAR2", "value2");
//     set_env(&env_list, "VAR3", "value3");

//     return env_list;
// }

// // テスト用のメイン関数
// int main()
// {
//     t_env *env_list = create_fake_envlist(); // フェイク環境変数リストを作成

//     // テスト: create_environ 関数を呼び出し、環境変数配列を作成
//     char **environ = create_environ(&env_list);

//     // 作成した環境変数配列の内容を表示
//     printf("Environment Variables:\n");
//     for (int i = 0; environ[i] != NULL; i++)
//     {
//         printf("%s\n", environ[i]);
//         free(environ[i]); // メモリの解放
//     }

//     free(environ); // 環境変数配列全体のメモリを解放
//     // free_env_list(&env_list); // フェイク環境変数リストのメモリを解放

//     return 0;
// }
