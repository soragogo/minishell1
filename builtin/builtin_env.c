#include "./../includes/minishell.h"

//arg消そう
int ft_env(t_env **env_head)
{
	t_env *tmp;

	tmp = *env_head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

// int main(){
// 	char *arg = "env TEST_VARIABLE=hello";
// 	t_env *map = map_new();
//     envmap_init(&map);
// 	ft_env(&map, arg);
// 	return 0;
// }