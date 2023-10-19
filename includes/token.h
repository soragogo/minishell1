/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:51:41 by mayu              #+#    #+#             */
/*   Updated: 2023/10/19 17:54:59 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
	int					is_freed;
	struct s_list_token	*next_token;
}	t_token;

t_token	*ft_tokenizer(char *command);
char	*skip_spaces(char *str);
int		is_dilimeter(char c);
void	split_into_tokens(t_token *tokens, char *command, int num_of_tokens);

#endif
