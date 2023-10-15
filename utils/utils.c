#include "../includes/minishell.h"

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

char  *env_join(char *name, char *value, char **environ)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strjoin(name, "=");
	environ[0] = ft_strjoin(tmp, value);
	free(tmp);//最後だけfreeできないなんで？
	return (environ[0]);
}

//KEY=valueの形で環境変数を作成する関数
char **create_environ(t_env **env_head)
{
	t_env *tmp;
	char **environ;
    int i;
	int env_num;

    i = 0;
	tmp = *env_head;
	env_num = count_env(*env_head);
	environ = (char **)malloc(sizeof(char *) * env_num + 1);
	while (tmp)
	{
		env_join(tmp->name, tmp->value, &environ[i]);
		tmp = tmp->next;
		i++;
	}
    environ[i] = NULL;
	return (environ);
}

void free_environ(char **environ)
{
    int i = 0;
    while (environ[i])
    {
        free(environ[i]);
        i++;
    }
    // free(environ[i]);
	free(environ);
}

/* -------------------------------------------------------------- */


// // テスト用のフェイク環境変数リストを作成する関数
// t_env *create_fake_envlist()
// {
//     t_env *env_list = NULL;

// 	envmap_init(&env_list);
//     set_env(&env_list, "VAR1", "value1", false);
//     set_env(&env_list, "VAR2", "value2", false);
//     set_env(&env_list, "VAR3", "value3", false);

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
// 	int i = 0;
//     // while (environ[i])
//     // {
//     //     printf("%s\n", environ[i]);
//     //     free(environ[i]); // メモリの解放
// 	// 	i++;
//     // }
// 	free_environ(environ);
// 	free_map(&env_list);
//     return 0;
// }



// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }