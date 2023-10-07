#include "./../includes/minishell.h"

// void dup_envlist(t_env **env_head, t_env **tmplist)
// {
// 	// t_env *tmp;
// 	// t_env *tmp2;
// 	// size_t i;

// 	// i = 0;
// 	// tmp = *env_head;
// 	// while (tmp)
// 	// {
// 	// 	// tmp2 = malloc(sizeof(t_env));
// 	// 	// if (tmp2 == NULL)
// 	// 	// 	printf("malloc error");//error
// 	// 	tmplist[i]->name = ft_strdup(tmp->name);
// 	// 	tmplist[i]->value = ft_strdup(tmp->value);
// 	// 	// tmplist[i]->next = tmp->next;
// 	// 	tmp = tmp->next;
// 	// 	i++;
// 	// }
// 	// extern char **environ;
// 	char **env;
// 	char *name;
// 	char *value;

// 	// *tmplist = NULL;
// 	env = create_environ(env_head);
//     while(*env) {
//         name = get_env_name(name, *env);
// 		value = get_env_value(value, *env);
// 		if (set_env(tmplist, name, value) == -1)
// 			printf("error");
// 		env++;
// 	}
// }

// void sort_envlist(t_env **tmplist)
// {
// 	//NAMEをaskii順にソート
// 	while (*tmplist){
// 		if (strcmp((*tmplist)->name, (*tmplist)->next->name) > 0)
// 		{
// 			//swap
// 			char *tmp_name;
// 			char *tmp_value;

// 			tmp_name = (*tmplist)->name;
// 			tmp_value = (*tmplist)->value;
// 			(*tmplist)->name = (*tmplist)->next->name;
// 			(*tmplist)->value = (*tmplist)->next->value;
// 			(*tmplist)->next->name = tmp_name;
// 			(*tmplist)->next->value = tmp_value;
// 			*tmplist = (*tmplist)->next;
// 		}
// 	}
// }

int display_envlist(t_env **env_head)
{
	t_env *tmp;
	t_env *tmplist;
	size_t count;

	// count = count_env(*env_head);
	// if (count == 0)
	// 	return (0);
	// tmplist = malloc(sizeof(t_env) * count);
	// if (!tmplist)
	// 	fatal_error("malloc error");//error
	// dup_envlist(env_head, &tmplist);
	// sort_envlist(&tmplist);
	// tmp = tmplist;
	tmp = *env_head;
	while (tmp)
	{
		if (tmp->name){
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(tmp->value, STDOUT_FILENO);
				ft_putendl_fd("\"", STDOUT_FILENO);
			}
			tmp = tmp->next;
		}
	}
	// free(tmplist);
	return (0);
}

int ft_export(t_env **map, char **commands)
{
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	if (commands[1] == NULL)//引数を取らない場合、一覧表示
	{
		display_envlist(map);
		return (0);
	}
	if (ft_strchr(commands[1], '=') == NULL)//=がない場合、エラー
	{
		return (0);
	}
	name = get_env_name(name, commands[1]);
	value = get_env_value(value, commands[1]);
	if(set_env(map, name, value) == -1)//環境変数をセット
	{
		error_message("export", NULL, "not a valid identifier");
		return (1);
	}
	return (0);
}

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

//     // テスト1: 引数なしで ft_export を呼び出す（一覧表示）
//     char *test1_commands[] = {"export", NULL};
//     printf("Test 1: Display Environment List\n");
//     ft_export(&env_list, test1_commands);

//     // テスト2: 環境変数を新しく追加して ft_export を呼び出す
//     char *test2_commands[] = {"export", "NEW_VAR=new_value", NULL};
//     printf("\nTest 2: Add New Environment Variable\n");
//     ft_export(&env_list, test2_commands);
//     ft_export(&env_list, test1_commands); // 一覧を再度表示

//     // テスト3: 既存の環境変数を更新して ft_export を呼び出す
//     char *test3_commands[] = {"export", "VAR1=new_value1", NULL};
//     printf("\nTest 3: Update Existing Environment Variable\n");
//     ft_export(&env_list, test3_commands);
//     ft_export(&env_list, test1_commands); // 一覧を再度表示

//     // メモリのクリーンアップ
//     // free_env_list(&env_list);

//     return 0;
// }

