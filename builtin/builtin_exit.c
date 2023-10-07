#include "../includes/minishell.h"

int is_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int ft_exit(char **command, t_info *info)
{
	int status;
	char *arg;

	status = 0;
	if (command[1] == NULL)
		status = info->exit_status_log;//前回の終了コード
	else if (command[2])
	{
		error_message("exit", NULL, "too many arguments");
		return (1);
	}
	else
	{
		if (is_num(command[1]) == 0)
		{
			error_message("exit", command[1], "numeric argument required");
			exit(255);
		}
		else
			status = ft_atoi(command[1]) % 255;
	}
	exit (status);
}


// int main(void) {
//     char *command[] = {"exit", "42", NULL}; // コマンドと引数の例
//     t_info info;
//     info.exit_status_log = 0; // 仮の exit ステータス

//     int result = ft_exit(command, &info);

//     if (result == 1) {
//         printf("Error: Too many arguments\n");
//     } else {
//         printf("Program exited with status: %d\n", info.exit_status_log);
//     }

//     return 0;
// }
