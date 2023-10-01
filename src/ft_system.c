#include "../includes/minishell.h"

// void fatal_error(const char *msg) __attribute__((noreturn));

void fatal_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int ft_system(t_token *tokens, int *status)
{
	pid_t pid;
	//char *commands[] = {"bash", "-c", command, NULL};
	//	char *commands[] = {"/bin/bash", "-c", "cat <<a", NULL};
	extern char **environ;

	pid = fork();
	char *token_twod[10000];
	int i = 0;

	// search_path(tokens);
	while (tokens[i].arg != NULL)
	{
		token_twod[i] = tokens[i].arg;
		i++;
	}
	token_twod[i] = NULL;
//	for (int i = 0; token_twod[i] != NULL; i++)
//		printf("token_twod[%d]: [%s]\n",i,  token_twod[i]);

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
				return -1;
			}
		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
		*status = WEXITSTATUS(*status);
	}
	else
		return (-1);
	return WIFEXITED(*status);
}
