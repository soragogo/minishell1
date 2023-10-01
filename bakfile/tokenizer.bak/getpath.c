#include "token.h"

t_token *ft_tokenizer(char *command);

void convert_env_variables(t_token *tokens)
{
	char *env;
	char *tmp;
	for (int i = 0; tokens[i].arg != NULL; i++)
	{
		env = strchr(tokens[i].arg, '$');
		if (env)
		{
			env++;
			tmp = getenv(env);
			if (tmp)
			{
				free(tokens[i].arg);
				tokens[i].is_freed = 1;
				tokens[i].arg = tmp;
			}
		}
	}
}

/*
int main()
{
	t_token *tokens;
	t_token *env_converted_tokens;
	char *command;
	while (1)
	{
		command = readline("test here> ");
		tokens = ft_tokenizer(command);
		convert_env_variables(tokens);
		for (int i = 0; tokens[i].arg != NULL; i++)
		{
			puts("------------------------");
			printf("token[%d] :[%s]\n", i, tokens[i].arg);
			if (tokens[i].is_freed == 0)
				free(tokens[i].arg);
		}
		free(tokens);
		free(command);

	}
	exit;

}*/
