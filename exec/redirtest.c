#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

// void redirect(t_commandset *commands, t_info *info)
// {
// 	while (commands->node){
// 		handle_redirection(commands, info);
// 		commands->node = commands->node->next;
// 	}
// }

void handle_redirection(t_commandset *commands, t_info *info)
{
	t_redirect *tmp_node;

	tmp_node = commands->node;
	while (tmp_node){
		if (tmp_node->filename == NULL)
			return ;
		if (tmp_node->type == REDIRECT_OUT)
		{
			redirect_out(tmp_node);
		}
		else if (tmp_node->type == REDIRECT_IN)
		{
			redirect_in(tmp_node);
		}
		else if (tmp_node->type == APPEND_OUT)
		{
			append(tmp_node);
		}
		else if (tmp_node->type == HERE_DOCUMENT)
		{
			here_document(tmp_node, info);
		}
		tmp_node = tmp_node->next;
	}
}
// if (commands->node->filename == NULL)
// 			return ;
// 		if (commands->node->type == REDIRECT_OUT)
// 		{
// 			redirect_out(commands->node);
// 		}
// 		else if (commands->node->type == REDIRECT_IN)
// 		{
// 			redirect_in(commands->node);
// 		}
// 		else if (commands->node->type == APPEND_OUT)
// 		{
// 			append(commands->node);
// 		}
// 		else if (commands->node->type == HERE_DOCUMENT)
// 		{
// 			here_document(commands->node, info);
// 		}

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

void here_document(t_redirect *node, t_info *info)
{
	// int fd;

	node->oldfd = STDIN_FILENO;
	node->newfd = heredoc(node->filename, info->map_head);
	do_redirect(node);
	// printf("\nfd:%d\n", command->node->newfd);
}

void do_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	node->stashfd = dup(node->oldfd);//STDOUT_FILENOを一時保存
	dup2(node->newfd, node->oldfd);//bのfdをSTDOUT_FILENOにコピー
	// do_redirect(node->next);
}

void undo_redirect(t_redirect *node)
{
	if (node == NULL)
		return ;
	undo_redirect(node->next);
	dup2(node->stashfd, node->oldfd);//一時保存したSTDOUT_FILENOを復元
	// if (node->prev == NULL)
	// 	return ;
	close(node->stashfd);
	close(node->newfd);
}

int heredoc(const char *delimiter, t_env *env_head)
{	//pipeの読み込み側fdを返す
	int pipefd[2];
	char *line;
	int count;
	size_t d_len;
	int i;

	count = 0;
	pipe(pipefd);
	d_len = ft_strlen(delimiter);
	while(1){
		line = readline("> ");
		if (only_space(line) == FALSE){
			i = skip_space(&line);
			while(i > 0){
				write(pipefd[1], " ", 1);
				i--;
			}
			line = expand_quote(line, env_head);
			if (line == NULL)
				break ;
			if (ft_strncmp(line, delimiter, d_len + 1) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
		}
		write(pipefd[1], "\n", 1);
		free(line);
		count++;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}




/* --------------------------------------------------------------- */

// int main() {
//     t_env *env_head = NULL; // 環境変数リストを初期化または設定
//     t_info info; // 任意の情報構造体を初期化または設定

//     // ヒアドキュメントをテストするために、デリミタとして"END"を使用
//     const char *delimiter = "END";

//     int heredoc_fd = heredoc(delimiter, env_head);

//     close(heredoc_fd); // ファイルディスクリプタをクローズ

//     return 0;
// }
