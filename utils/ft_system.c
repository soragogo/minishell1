#include "../includes/minishell.h"

int ft_system(t_token *tokens, int *status)
{
	int			i;
	pid_t		pid;
	extern char	**environ;
	char		*token_twod[10000];

	i = 0;
	pid = fork();
	while (tokens[i].arg != NULL)
	{
		token_twod[i] = tokens[i].arg;
		i++;
	}
	token_twod[i] = NULL;
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		execve(token_twod[0], token_twod, environ);
		fatal_error("minishell");
	}
	else if (pid > 0)
	{
		do
		{
			if (waitpid(pid, status, 0) == -1)
			{
				return (-1);
			}
		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
		*status = WEXITSTATUS(*status);
	}
	else
		return (-1);
	return WIFEXITED(*status);
}
