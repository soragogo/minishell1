#include "./../includes/minishell.h"

int ft_export(t_env **map, char **commands)
{
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	if (commands[1] == NULL)//引数を取らない場合、一覧表示
	{
		ft_env(map);
		return (0);
	}
	if (strchr(commands[1], '=') == NULL)//=がない場合、エラー
	{
		return (0);
	}
	name = get_env_name(name, commands[1]);
	value = get_env_value(value, commands[1]);
	if(set_env(map, name, value) == -1)//環境変数をセット
	{
		printf("error");
		return (-1);
	}
	return (0);
}


// void test_ft_export(t_env **map, char **arg) {
//     printf("Setting environment variable: %s\n", *arg);
//     ft_export(map, arg);
//     printf("Environment variable set.\n\n");
// }

// int main() {
//     // テストケースを用意して実行
//     t_env *map = map_new();
//     envmap_init(&map);  // mapの初期化は実際の状況に合わせて修正
    

//     // char *test1 = "MY_VARIABLE=value123";
// 	char *test1[] = {"export", "MY_VARIABLE=value123"};
// 	ft_env(&map, *test1);
//     test_ft_export(&map, test1);

//     char *test2[] = {"export", "ANOTHER_VARIABLE=hello_world"};
//     test_ft_export(&map, test2);
	
// 	printf("----------------------------------------\n");
// 	ft_env(&map, *test1);

//     return 0;
// }