#include "../includes/minishell.h"

//内部のエラー、exitする
void fatal_error(char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

//コマンドのエラー、エラーメッセージ表示
void error_message(char *command, char *arg, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    if (command)
    {
        ft_putstr_fd(command, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    if (arg)
    {
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putendl_fd(msg, STDERR_FILENO);
}