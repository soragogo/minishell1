/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:34 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/07 15:22:13 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "token.h"
#include "../libft/libft.h"

typedef struct s_node
{
	int newfd;
	int stashfd;
	int oldfd;
	TYPE type;
	const char *filename;
	struct s_node *next;
	struct s_node *prev;
} t_redirect;

typedef struct s_commandset
{
	t_redirect *node;
	char **command;
	// int in_fd;
	// int out_fd;
	pid_t pid;
	struct s_commandset *next;
	struct s_commandset *prev;
} t_commandset;

void import_redirection(t_token *tokens, t_commandset *commandsets, int num_of_commands);
void test_commandsets(t_commandset *commandsets, int num_of_commands);
int count_commandset(t_token *tokens);
void categorize_tokens(t_token *tokens);
t_commandset *create_command_pipeline(t_token *tokens, int num_of_commands);
int count_command(t_token *tokens);
void import_command(t_token *tokens, t_commandset *commandsets, int num_of_commands);
void free_parser(t_commandset *commandsets);
t_commandset *ft_parser(char *buff);
int count_redirection(t_token *tokens, int current_pipe);
void connect_redirections(t_redirect *node, int count);
void import_redirection(t_token *tokens, t_commandset *commandsets, int num_of_commands);

#endif
