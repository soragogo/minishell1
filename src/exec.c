#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

//コマンドがbuiltinかを確かめる関数
int is_builtin(t_commandset *command){
	const char *builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int i = 0;

	while (builtin[i] != NULL)
	{
		if (strcmp(*command[0].command, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//builtinコマンドを実行する関数
int exec_builtin(t_commandset *commands, t_info *info)
{
	int status;

	status = 0;
	//後でredirectの処理を書く

	if (strcmp(*commands[0].command, "echo") == 0)
		status = ft_echo(commands->command, info->exit_status_log);
	else if (strcmp(*commands[0].command, "cd") == 0)
		status = ft_chdir(commands->command, &(info->map_head));
	else if (strcmp(*commands[0].command, "env") == 0)
		status = ft_env(&(info->map_head));
	else if (strcmp(*commands[0].command, "pwd") == 0)
		status = ft_pwd();
	else if (strcmp(*commands[0].command, "export") == 0)
		status = ft_export(&info->map_head, commands->command);
	else if (strcmp(*commands[0].command, "unset") == 0)
		status = ft_unset(&info->map_head, commands->command);
	else if (strcmp(*commands[0].command, "exit") == 0)
		status = ft_exit(commands->command, info);
	else
		return (-1);
	return (status);
}

// int saved_stdin;

// saved_stdin = dup(STDIN_FILENO);
// //
// dup2(saved_stdin, STDIN_FILENO);
// close(saved_stdin);

void handle_pipe(int left_pipe[2], int right_pipe[2], t_commandset *command)
{
	if (command->prev)
	{
    //     dprintf(2, "pipe[0] %d ::::: pipe[1] %d\n", left_pipe[0], left_pipe[1]);
		//コマンドの入力をパイプから受け取る
		dup2(left_pipe[0], STDIN_FILENO);
		close(left_pipe[1]);
		close(left_pipe[0]);
	}
	if (command->next)
	{
        // dprintf(2, "pipe[0] %d ::::: pipe[1] %d\n", right_pipe[0], right_pipe[1]);
		//コマンドの出力先をパイプに変更
		dup2(right_pipe[1], STDOUT_FILENO);
		close(right_pipe[0]);
		close(right_pipe[1]);
	}
}

void create_pipe(t_commandset *command, int new_pipe[2]){
	if (command->next){
		if (pipe(new_pipe) < 0)
			printf("pipe error");
	}
}

int exec_command(t_commandset *commands, t_info *info){
	int status;
	static int new_pipe[2];
	static int old_pipe[2];
	char *path;
	char **my_environ;
	pid_t pid;

	status = 0;
	create_pipe(commands, new_pipe);
	my_environ = create_environ(&(info->map_head));
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0){//子プロセス
		handle_pipe(old_pipe, new_pipe, commands);
		handle_redirection(commands, info);
		if (is_builtin(commands) != -1)
		{
			// write(1, "builtin\n", 8);
			status = exec_builtin(commands, info);
		}
		else
		{
			// write(1, "not builtin\n", 12);
			path = fetch_path(*commands->command, &(info->map_head));
			status = execve(path, commands->command, my_environ);
			if (status == -1)
			{
				printf("minishell: %s: command not found\n", *commands->command);
				exit(127);
			}
		}
		undo_redirect(commands);
	}
    if (old_pipe[0] != 0)
        close(old_pipe[0]);
    if (old_pipe[1] != 0)
        close(old_pipe[1]);
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
	commands->pid = pid;
	return (status);
}

void wait_command(t_commandset *commands){
	int status;
	if (waitpid(commands->pid, &status, 0) < 0)
		printf("waitpid error\n");
}


int handle_command(t_commandset *commands, t_info *info)
{
	int status;

	status = 0;
	//pipeなし
	if (commands[1].node == NULL && is_builtin(commands) != -1)//fork()いらない
	{
		status = exec_builtin(commands, info);
	}
	else//fork()必要
	{
		while (commands != NULL)
		{
			status = exec_command(commands, info);
			wait_command(commands);
			commands = commands->next;
		}
	}
	return (status);
}


/* --------------------------------------------------------- */


// #include "../includes/minishell.h"
// #include "../tokenizer/token.h"
// #include "../tokenizer/parser.h"

// int main() {
//     t_commandset commands[3];
    
//     // コマンド1
//     commands[0].command = malloc(sizeof(char *) * 3);
// 	commands[0].command[0] = "exit";
// 	commands[0].command[1] = NULL;
// 	commands[0].command[2] = NULL;
// 	commands[0].node = (t_redirect *)malloc(sizeof(t_redirect));
// 	commands[0].node->oldfd = 1;
//     // commands[0].command = {"cat", "a.out"};
// 	// commands[0].next = &commands[1];
// 	commands[0].next = NULL;
// 	commands[0].prev = NULL;
// 	// commands[0].node->filename = "b.txt";
// 	// commands[0].node->type = REDIRECT_OUT;
// 	// commands[0].node->next = NULL;
// 	// commands[0].node->prev = NULL;
    
//     // // コマンド2
//     // commands[1].command = malloc(sizeof(char *) * 2);
// 	// commands[1].command[0] = "cat";
// 	// commands[1].command[1] = "b.txt";
// 	// commands[1].command[2] = NULL;
// 	// commands[1].node = (t_redirect *)malloc(sizeof(t_redirect));
// 	// commands[1].node->oldfd = 1;
// 	// commands[1].next = &commands[2];
// 	// // commands[1].next = NULL;
// 	// commands[1].prev = &commands[0];

// 	// commands[2].command = malloc(sizeof(char *) * 2);
// 	// commands[2].command[0] = "wc";
// 	// commands[2].command[1] = NULL;
// 	// commands[2].node = (t_redirect *)malloc(sizeof(t_redirect));
// 	// commands[2].node->oldfd = 1;
//     // // commands[0].command = {"cat", "a.out"}; // 実行したいコマンドのパスを指定します。
// 	// commands[2].next = NULL;
// 	// commands[2].prev = &commands[1];

//     // コマンドを実行
//     t_env *map;
// 	map = map_new();
//     envmap_init(&map);
// 	t_info info;
// 	info.map_head = map;
//     int status = handle_command(commands, &info);

//     if (status == -1) {
//         printf("コマンドの実行に失敗しました。\n");
//     } else {
//         printf("コマンドの実行が正常に完了しました。終了コード: %d\n", status);
//     }

//     return 0;
// }


