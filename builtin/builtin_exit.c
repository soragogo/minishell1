#include "../includes/minishell.h"

int ft_exit(char **command, t_info *info)
{
	char *arg;
	if (command[1] == NULL)
		exit(info->exit_status_log);//前回の終了コード
	else if (command[2])
	{
		printf("exit: too many arguments");
		return (1);
	}
	else
	{
		if (ft_isdigit(command[1] == 0))
			exit (atoi(command[1]) % 255);
	}
	exit (255);
}