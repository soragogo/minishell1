#include "./../includes/minishell.h"

int ft_unset(t_env **env_head, char **commands)
{
	int i;

	i = 1;
	while (commands[i] != NULL)
	{
		env_unset(env_head, commands[i]);
		i++;
	}
	return (0);
}

// void test_ft_unset(t_env **env_head, char **name) {
// 	printf("Unsetting environment variable: %s\n", name[1]);
// 	ft_unset(env_head, name);
// 	printf("Environment variable unset.\n\n");
// }

// int main() {
// 	// テストケースを用意して実行
// 	t_env *env = map_new();
//     envmap_init(&env);

// 	char *test1[] = {"unset", "TEST_VARIABLE1"};
// 	test_ft_unset(&env, test1);
// 	set_env(&env, "TEST_VARIABLE2", "hello");
// 	ft_env(&env, "TEST_VARIABLE2");
// 	printf("----------------------------------------\n");
// 	char *test2[] = {"unset", "TEST_VARIABLE2"};
// 	test_ft_unset(&env, test2);
// 	ft_env(&env, "TEST_VARIABLE2");
// 	return 0;
// }
