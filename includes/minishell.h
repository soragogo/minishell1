#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>

#include "../libft/libft.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"


int ft_system(t_token *tokens, int *status);
// int ft_chdir(char *command_buf);
void ft_signals(void);
void waitline();
char *search_path(char *command);


typedef struct s_env	t_env;
typedef struct s_info	t_info;

typedef struct s_env
{
	char *name;					//環境変数名
	char *value;				//値
	struct s_env *next;
} t_env;

typedef struct	s_info
{
	t_env	*map_head;			//環境変数のリスト
	int		exit_status_log;	//直前のコマンドの終了ステータス
	// t_token *tokens;			//
	// t_command *command;

}	t_info;


// int ft_system(char *command, int *status);
// int ft_chdir(char *command_buf);
void ft_signals(void);
void waitline();


	/* parser */
// void ft_parser(char *buff);
t_commandset *ft_parser(char *buff);
// t_commandset *create_command_pipeline(t_token *tokens, int num_of_commands);

	/* env function */
t_env	*map_new(void);
char	*get_env_name(char *ret, char *env);
char	*get_env_value(char *ret, char *env);
void	envmap_init(t_env **map);
int		set_env(t_env **env_head, char *name, char *value);
t_env	*item_new(t_env *new_env, char *name, char *value);
void	add_new(t_env **map, t_env *new_env);
void	env_unset(t_env **env_head, char *delete_env_key);
char	*map_get(t_env **env_head, char *name);
void	free_map(t_env **map);
char **create_environ(t_env **env_head);


	/* builtin command */
int ft_echo(char **command, int status);
int ft_chdir(char **commands, t_env **env);
int	ft_pwd(void);
int ft_exit(char **command, t_info *info);
int ft_unset(t_env **env_head, char **commands);
int	ft_env(t_env **env_head);
int ft_export(t_env **map, char **commands);

	/* redirection */
void handle_redirection(t_commandset *commands);
void redirect_out(t_redirect *node);
void redirect_in(t_redirect *node);
void here_document(t_commandset *command);
void do_redirect(t_redirect *node);
void undo_redirect(t_commandset *commands);
int heredoc(const char *delimiter);
void append(t_redirect *node);

	/* utils */
int is_builtin(t_commandset *command);
int exec_builtin(t_commandset *commands, t_info *info);
char **join(char const *s1, char const *s2, char **environ);
void env_join(char *name, char *value, char **environ);
char *fetch_path(char *file, t_env **map);
int handle_command(t_commandset *commands, t_info *info);


#endif
