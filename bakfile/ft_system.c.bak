#include "minishell.h"

void fatal_error(const char *msg) __attribute__((noreturn));

void fatal_error()
{
	
	exit(1);
}

int ft_system(char *command, int *status)
{
	pid_t pid;
	char *commands[] = {"bash", "-c", command, NULL};
//	char *commands[] = {"/bin/bash", "-c", "cat <<a", NULL};
	extern char **environ;

	pid = fork();

	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		execve("/bin/bash", commands, environ);
		fatal_error("execve");
	}
	else if (pid > 0)
	{
		do
		{
			if (waitpid(pid, status, 0) == -1)
			{
				return -1;
			}
		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
		*status = WEXITSTATUS(*status);
	}
	else
		return (-1);
	return WIFEXITED(*status);
}
