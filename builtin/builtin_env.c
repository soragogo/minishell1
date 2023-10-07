#include "./../includes/minishell.h"

int ft_env(t_env **env_head)
{
	t_env *tmp;

	tmp = *env_head;
	while (tmp)
	{
		if(tmp->value)
		{
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
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