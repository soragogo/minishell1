#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"
#include "../gnl/get_next_line_bonus.h"

void handle_redirection(t_commandset *commands, t_info *info)
{
	if (commands->node->filename == NULL)
		return ;
	if (commands->node->type == REDIRECT_OUT)
	{
		redirect_out(commands->node);
	}
	else if (commands->node->type == REDIRECT_IN)
	{
		redirect_in(commands->node);
	}
	else if (commands->node->type == APPEND_OUT)
	{
		append(commands->node);
	}
	else if (commands->node->type == HERE_DOCUMENT)
	{
		here_document(commands, info);
	}
}

void append(t_redirect *node)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	do_redirect(node);
	// printf("\nfd:%d\n", node->newfd);
}

void redirect_out(t_redirect *node)
{
	node->oldfd = STDOUT_FILENO;
	node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	do_redirect(node);
	// printf("\nfd:%d\n", node->newfd);
}

void redirect_in(t_redirect *node)
{
	node->oldfd = STDIN_FILENO;
	node->newfd = open(node->filename, O_RDONLY);
	do_redirect(node);
	// printf("\nfd:%d\n", node->newfd);
}

void here_document(t_commandset *command, t_info *info)
{
	// int fd;

	command->node->oldfd = STDIN_FILENO;
	command->node->newfd = heredoc(command->node->filename, info->map_head);
	do_redirect(command->node);
	// printf("\nfd:%d\n", command->node->newfd);
}

void do_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	node->stashfd = dup(node->oldfd);//STDOUT_FILENOを一時保存
	dup2(node->newfd, node->oldfd);//bのfdをSTDOUT_FILENOにコピー
	do_redirect(node->next);
}

void undo_redirect(t_commandset *commands)
{
	if (commands->node->filename == NULL)
		return ;
	undo_redirect(commands->next);
	dup2(commands->node->stashfd, commands->node->oldfd);//一時保存したSTDOUT_FILENOを復元
	close(commands->node->newfd);
}

int heredoc(const char *delimiter, t_env *env_head)
{	//pipeの読み込み側fdを返す
	int pipefd[2];
	char *line;
	char **buf;
	int i;

	i = 0;
	pipe(pipefd);
	printf("%s\n", delimiter);
	while(1){
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		i++;
		free(line);
	}
	// printf("i: %d\n", i);
	// buf = malloc(sizeof(char *) * (i + 1));
	// //pipefd[1]の中身をbufにコピー
	// int j;
	// j = 0;
	// while (j < i)
	// {
	// 	buf[j] = get_next_line(pipefd[0]);
	// 	j++;
	// }
	// buf[j] = NULL;
	// expand_env(buf, env_head);
	// i = 0;
	// while (buf[i])
	// {
	// 	printf("buf[%d]: %s\n", i, buf[i]);
	// 	write(pipefd[1], buf[i], strlen(buf[i]));
	// 	write(pipefd[1], "\n", 1);
	// 	i++;
	// }
	close(pipefd[1]);
	return (pipefd[0]);
}
