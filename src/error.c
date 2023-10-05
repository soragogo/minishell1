#include "../includes/minishell.h"

//内部のエラー、exitする
void fatal_error(char *command)
{
    error_message(command, NULL, strerror(errno));
	exit(EXIT_FAILURE);
}

//コマンドのエラー、エラーメッセージ表示
void error_message(char *command, char *file, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(command, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (file){
        ft_putstr_fd(file, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putendl_fd(msg, STDERR_FILENO);
}