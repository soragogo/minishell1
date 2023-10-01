#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

void free_before_closing(t_token *tokens, char *command_buf)
{
	for (int i = 0; tokens[i].arg != NULL; i++)
	{
		if (tokens[i].is_freed == 0)
			free(tokens[i].arg);
	}
	free(tokens);
	free(command_buf);
}

char *ft_readline()
{
	char *command_buf;
	command_buf = readline("minishell> ");
	if (command_buf)
		add_history(command_buf);
	return (command_buf);
}

int main()
{
	char *command_buf;
	int status;
	t_token *tokens;
	t_env *env;
	t_info info;
	t_commandset *commands;
	
	envmap_init(&env);//info_initの方がいいか
	info.map_head = env;
	while (1)
	{
		ft_signals();
		command_buf = ft_readline();
		if (!command_buf)
			break;
		if (*command_buf == '\0')
			continue ;
		// char command_buf[] = "cd ~";
		// tokens = ft_tokenizer(command_buf);
		commands = ft_parser(command_buf);
		// commands = create_command_pipeline(tokens);
		expand_env(commands->command, info.map_head);
		handle_command(commands, &info);
		/* ------------------ exec_command ---------------------- */
		// status = is_builtin(tokens, &info);//builtinだったら実行
		// if (status == -1)
		// 	ft_system(tokens, &status);//builtin以外のコマンドを実行
		// info.exit_status_log = status;
		/*--------------------------------------------------------*/
		// if (ft_strncmp(command_buf, "cd", 2) == 0 && (command_buf[2] == '\0' || command_buf[2] == ' '))
		// 	status = ft_chdir(&command_buf, &env);
		// else if (ft_strncmp(command_buf, "echo $?", 8) == 0)//直前のコマンドの終了ステータスを表示
		// {
		// 	printf("%d\n", status);
		// 	status = 0;
		// }
		// else
		// 	ft_system(tokens, &status);//builtin以外のコマンドを実行する関数
		// free_before_closing(tokens, command_buf);
	}
	return (0);
}
/*
__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}*/
