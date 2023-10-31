/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:34 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/31 15:50:17 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <libc.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

typedef enum type
{
	UNCATEGORIZED,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	APPEND_OUT,
	HERE_DOCUMENT,
	COMMAND,
	COMMAND_OPTION,
	FILE_NAME
}	t_type;

typedef struct s_list_token
{
	char				*arg;
	t_type				type;
}	t_token;

typedef struct s_node
{
	int				newfd;
	int				stashfd;
	int				oldfd;
	t_type			type;
	const char		*filename;
	struct s_node	*next;
	struct s_node	*prev;
}	t_redirect;

typedef struct s_commandset
{
	t_redirect			*node;
	char				**command;
	pid_t				pid;
	struct s_commandset	*next;
	struct s_commandset	*prev;
}	t_commandset;

t_commandset	*create_command_pipeline(int num_of_commands);
void			free_tokens(t_token *tokens);
void			categorize_tokens(t_token *tokens);
int				count_commandset(t_token *tokens);
int				count_command(t_token *tokens, int current_cmd);
void			import_command(t_token *tokens,
					t_commandset *commandsets, int num_of_commands);
void			import_redirection(t_token *tokens,
					t_commandset *commandsets, int num_of_commands);
void			test_commandsets(t_commandset *commandsets,
					int num_of_commands);
int				syntax_error(t_token *tokens);
void			free_commandset(t_commandset *csets);
t_token			*ft_tokenizer(char *command);
char			*skip_spaces(char *str);
int				is_dilimeter(char c);
void			split_into_tokens(t_token *tokens,
					char *command, int num_of_tokens);
int				return_end_of_env(char *end);
int				bracket_error(t_token *tokens, char l_br, char r_br);
int				count_nonempty_tokens(t_token *tokens);
void			import_nonempty_token(t_token *new_tokens, t_token *tokens);
t_token			*remove_empty_tokens(t_token *tokens);
t_commandset	*process_tokens(t_token *tokens);
#endif
