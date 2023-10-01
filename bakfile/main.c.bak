#include "minishell.h"




int main()
{
	char *command_buf;
	int status;
	while (1)
	{
		ft_signals();

		command_buf = readline("minishell> ");
		if (!command_buf)
			break ;
		else
			add_history(command_buf);
		if (strncmp(command_buf, "cd", 2) == 0 && (command_buf[2] == '\0' || command_buf[2] == ' '))
			status = ft_chdir(command_buf);
		else if(strncmp(command_buf, "echo $?", 8) == 0)
			printf("%d\n", status);
		else
			ft_system(command_buf, &status);
		free(command_buf);
	}	return (0);
}
/*
__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}*/
