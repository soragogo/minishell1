#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"


void free_before_closing(t_commandset *command, char *command_buf)
{
    free_commandset(command);
    free(command_buf);
}
bool only_space(char *command)
{
	while (*command)
	{
		if (*command != ' ' &&  *command != '\t')
			return false;
		command++;
	}
	return true;
}

char *ft_readline(t_env *env_head)//
{
	char *command_buf;
	command_buf = readline("minishell> ");
	if (command_buf){
		add_history(command_buf);
	}
	return (command_buf);
}
