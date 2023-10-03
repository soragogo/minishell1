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

void copy_buf(char **buf, int fd);
void convert_heredoc(int fd, int pipefd, t_env *env_head, int count)
{
	char *line;
	char **buf;
	int i;

	i = 0;
	buf = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		buf[i] = malloc(sizeof(char) * 100);
		buf[i] = get_next_line(fd);
		i++;
	}
	buf[i] = NULL;
	expand_env(buf, env_head);
	close(fd);
	copy_buf(buf, pipefd);
}

void copy_buf(char **buf, int fd)
{
	int i;

	i = 0;
	while (buf[i])
	{
		write(fd, buf[i], strlen(buf[i]));
		write(fd, "\n", 1);
		i++;
	}
}


int heredoc(const char *delimiter, t_env *env_head)
{	//pipeの読み込み側fdを返す
	int pipefd[2];
	char *line;
	int count;
	int fd;

	count = 0;
	pipe(pipefd);
	// printf("%s\n", delimiter);
	delimiter = "END";//
	fd = open("tmp", O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
	char *line2[3];
	line2[0] = "dfghj";
	line2[1] = "dfghj2";
	line2[2] = "END";
	int i = 0;
	
	while(1){
		// line = readline("> ");
		line = line2[i];
		i++;
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			// free(line);
			break ;
		}
		// write(pipefd[1], line, strlen(line));
		// write(pipefd[1], "\n", 1);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		// read(fd, line, 100);
		// write(1, line, 100);
		// free(line);
		count++;
	}
	convert_heredoc(fd, pipefd[1], env_head, count);
	// copy_file_contents(pipefd[1], fd);
	close(pipefd[1]);
	read(pipefd[0], line, 100);
	write(1, line, 100);
	return (pipefd[0]);
}




/* --------------------------------------------------------------- */

int main() {
    t_env *env_head = NULL; // 環境変数リストを初期化または設定
    t_info info; // 任意の情報構造体を初期化または設定

    // ヒアドキュメントをテストするために、デリミタとして"END"を使用
    const char *delimiter = "END";

    int heredoc_fd = heredoc(delimiter, env_head);

    close(heredoc_fd); // ファイルディスクリプタをクローズ

    return 0;
}
