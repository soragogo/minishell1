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
#include "../includes/minishell.h"
#include "../tokenizer/token.h"

typedef struct s_redirect
{
	TYPE redir_type;
	int newfd;
	int stashfd;
	int oldfd;
	const char *filename;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}	t_redirect;

typedef struct s_commandset
{
	t_redirect *node;
	char **command;
	pid_t pid;
	struct s_commandset *next;
	struct s_commandset *prev;
} t_commandset;

#endif
