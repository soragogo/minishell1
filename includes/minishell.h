/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:00:37 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 17:28:48 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../includes/token.h"
# include "../includes/parser.h"

typedef struct s_env	t_env;
typedef struct s_info	t_info;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			is_env;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	t_env	*map_head;
	int		exit_status_log;
}	t_info;

int				ft_system(t_token *tokens, int *status);
void			ft_signals(void);
void			waitline(void);
char			*search_path(char *command);
void			ft_signals(void);
void			waitline(void);
t_commandset	*ft_parser(char *buff, int *status, t_env *env_head);
char			*deal_status(char *arg, int *i, int status, char *ret);

	/* env function */
char			*get_env_name(char *ret, char *env);
char			*get_env_value(char *ret, char *env);
void			envmap_init(t_env **map);
int				set_env(t_env **env_head, char *name, char *value, bool is_env);
t_env			*item_new(t_env *new_env, char *name, char *value);
void			add_new(t_env **map, t_env *new_env);
void			env_unset(t_env **env_head, char *delete_env_key);
char			*map_get(t_env **env_head, char *name);
void			free_map(t_env **map);
char			**create_environ(t_env **env_head);
size_t			count_env(t_env *env);

	/* builtin command */
int				ft_echo(char **command, int status);
int				ft_chdir(char **commands, t_env **env);
int				ft_pwd(void);
int				ft_exit(char **command, t_info *info);
int				ft_unset(t_env **env_head, char **commands);
int				ft_env(t_env **env_head);
int				ft_export(t_env **map, char **commands);
char			*convert_relative_path(char *dir_path, char *input);

	/* redirection */
void			redirect(t_commandset *commands, t_info *info);
void			handle_redirection(t_commandset *commands, t_info *info);
void			redirect_out(t_redirect *node);
void			redirect_in(t_redirect *node);
void			here_document(t_redirect *node, t_info *info);
void			do_redirect(t_redirect *node);
void			undo_redirect(t_redirect *node);
int				heredoc(const char *delimiter, t_info *info);
void			append(t_redirect *node);

	/* exec */
void			create_pipe(t_commandset *command, int new_pipe[2]);
void			handle_pipe(int left_pipe[2],
					int right_pipe[2], t_commandset *command);
int				wait_command(t_commandset *commands);

	/* utils */
int				is_builtin(t_commandset *command);
int				exec_builtin(t_commandset *commands, t_info *info);
char			**join(char *s1, char *s2, char **environ);
char			*env_join(char *name, char *value, char **environ);
char			*fetch_path(char *file, t_env **map);
int				handle_command(t_commandset *commands, t_info *info);
char			*expand_env(char *arg, int i, t_env *env_head, int *status);
int				ft_strcmp(char *s1, char *s2);
char			*expand_quote(char *command, t_env *env_head, int *status);
int				skip_space(char **str);
char			*ft_readline(void);
bool			only_space(char *command);
void			free_before_closing(t_commandset *command, char *command_buf);
void			free_environ(char **environ);

	/* error */
void			error_message(char *command, char *arg, char *msg);
void			fatal_error(char *msg);

t_token			*ft_tokenizer(char *command);
char			*skip_spaces(char *str);
int				is_dilimeter(char c);
void			split_into_tokens(t_token *tokens,
					char *command, int num_of_tokens);
char			*convert_relative_path(char *dir_path, char *input);
#endif
