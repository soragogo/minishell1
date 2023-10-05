#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void handler(int signum)
{
		if (signum == SIGQUIT)
		{
			rl_redisplay();
			return;
		}
		if (signum == SIGINT)
		{
			rl_on_new_line();
			ft_putchar_fd('\n', STDERR_FILENO);
			rl_redisplay();
		}
}


void ft_signals(void)
{
		signal(SIGQUIT, handler);
		signal(SIGINT, handler);
}
