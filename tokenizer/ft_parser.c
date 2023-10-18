/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:41 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/18 18:06:12 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

int count_commandset(t_token *tokens)
{
	int i = 0;
	int count = 0;
	if (tokens[0].arg != NULL)
		count++;
	while (tokens[i].arg != NULL)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return count;
}

void categorize_tokens(t_token *tokens)
{
	int i = 0;
	int command_flag = 0;
	while (tokens[i].arg != NULL)
	{
		if (strncmp(tokens[i].arg, "|", 2) == 0)
		{
			tokens[i].type = PIPE;
			command_flag = 0;
		}
		else if (strncmp(tokens[i].arg, ">", 2) == 0)
			tokens[i].type = REDIRECT_OUT;
		else if (strncmp(tokens[i].arg, "<", 2) == 0)
			tokens[i].type = REDIRECT_IN;
		else if (strncmp(tokens[i].arg, ">>", 3) == 0)
			tokens[i].type = APPEND_OUT;
		else if (strncmp(tokens[i].arg, "<<", 3) == 0)
			tokens[i].type = HERE_DOCUMENT;
		else if (tokens[i].arg[0] == '-' && command_flag == 1)
			tokens[i].type = COMMAND_OPTION;
		else if (i == 0 || (command_flag == 0 && i != 0 && (tokens[i - 1].type < REDIRECT_OUT || tokens[i - 1].type > HERE_DOCUMENT)))
		{
			tokens[i].type = COMMAND;
			command_flag = 1;
		}
		else if (i != 0 && (tokens[i - 1].type >= REDIRECT_OUT && tokens[i - 1].type <= HERE_DOCUMENT))
			tokens[i].type = FILE_NAME;
		else
			tokens[i].type = UNCATEGORIZED;

		i++;
	}
}

t_commandset	*create_command_pipeline(int num_of_commands)
{
	t_commandset	*commandsets;
	int i;

	commandsets = ft_calloc(num_of_commands, sizeof(t_commandset));
	i = 1;
	commandsets[0].prev = NULL;
	if (num_of_commands > 1)
		commandsets[0].next = &commandsets[1];
	while (i < num_of_commands - 1)
	{
		commandsets[i].next = &commandsets[i + 1];
		commandsets[i].prev = &commandsets[i - 1];
		i++;
	}
	commandsets[num_of_commands - 1].next = NULL;
	if (num_of_commands > 1)
		commandsets[num_of_commands - 1].prev = &commandsets[num_of_commands - 2];
	i = 0;
	while (commandsets[i].next != NULL)
		i++;
	return (commandsets);
}

int count_command(t_token *tokens, int current_cmd)
{
	int i = 0;
	int count = 0;
	while (current_cmd > 0)
	{
		while (tokens[i].arg && tokens[i].type != PIPE)
			i++;
		if (tokens[i].type == PIPE)
		{
			current_cmd--;
			i++;
		}
	}
	while (tokens[i].arg != NULL && tokens[i].type != PIPE)
	{
		if (tokens[i].type == COMMAND || tokens[i].type == COMMAND_OPTION || tokens[i].type == UNCATEGORIZED)
			count++;
		i++;
	}
	return count;
}

void import_command(t_token *tokens, t_commandset *commandsets, int num_of_commands)
{
	int i;
	int j;
	int k;
	int count;

	i = 0;
	j = 0;
	k = 0;
	count = 0;
	while (i < num_of_commands)
	{
		count = count_command(tokens, i);
		commandsets[i].command = ft_calloc(count + 1, sizeof(char *));

		while (tokens[j].arg != NULL && tokens[j].type != PIPE)
		{
			if (tokens[j].type == COMMAND || tokens[j].type == COMMAND_OPTION || tokens[j].type == UNCATEGORIZED)
			{
				commandsets[i].command[k] = ft_strdup(tokens[j].arg);
				k++;
			}
			j++;
		}
		commandsets[i].command[k] = NULL;
		k = 0;
		if (tokens[j].type == PIPE)
			j++;
		i++;
	}
}

void free_tokens(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].arg)
	{
		free(tokens[i].arg);
		i++;
	}
	free(tokens);
}

void free_commandset(t_commandset *csets)
{
    char *tmp_cmd;
    t_redirect *tmp_redir1;
    t_redirect *tmp_redir2;
    int i;
    int j;

	i = 0;
    while((i != 0 && csets[i - 1].next != NULL)|| i == 0)
    {
        tmp_cmd = csets[i].command[0];
        j = 0;
        while(tmp_cmd)
        {
            tmp_cmd = csets[i].command[j + 1];
            free(csets[i].command[j]);
            j++;
        }
        free(csets[i].command);
        j = 0;
        tmp_redir1 = csets[i].node;
        tmp_redir2 = csets[i].node;
        while (tmp_redir2)
        {
            tmp_redir2 = csets[i].node->next;
            free((char *)csets[i].node->filename);
            csets[i].node = tmp_redir2;
        }
        free(tmp_redir1);
        i++;
    }
    free(csets);
}

t_commandset *ft_parser(char *buff, int *status, t_env *env_head)
{
	t_token *tokens;
	t_token *tmp_token;
	t_commandset *commandsets;
	int num_of_commands;
	int i;

	i = 0;
	tokens = ft_tokenizer(buff);
	tmp_token = tokens;
	tokens = tmp_token;
	categorize_tokens(tokens);
	if (syntax_error(tokens))
	{
		*status = 258;
		free_tokens(tokens);
		return (NULL);
	}
	else
	{
		while (tokens[i].arg)
		{
			skip_space(&(tokens->arg));
			tokens[i].arg = expand_quote(tokens[i].arg, env_head, status);
			i++;
		}
		num_of_commands = count_commandset(tokens);
		// printf("num_of_commands: [%d]\n", num_of_commands);
		commandsets = create_command_pipeline(num_of_commands);
		import_command(tokens, commandsets, num_of_commands);
		import_redirection(tokens, commandsets, num_of_commands);
		// test_commandsets(commandsets, num_of_commands);
		free_tokens(tokens);
		// free_tokens(tokens);
	}
	// free_parser(commandsets);
	return (commandsets);
}

// #include "token.h"
// #include <stdio.h>
// #include <libc.h>
// int main()
// {
// 	char *buff;
// 	int status = 0;
// 	while (1)
// 	{
// 		buff = readline("test here> ");
// 		ft_parser(buff, &status);
// 		free(buff);
// 	}
// }
