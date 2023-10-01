#include "token.h"
#include "parser.h"
#include <stdbool.h>

int count_commands(t_token *tokens)
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

void connect_tokens(t_token *tokens)
{
	int i = 0;
	while (tokens[i].arg != NULL)
	{
		if (tokens[i].type == PIPE)
		{
			tokens[i].next_token = NULL;
		}
		else if (tokens[i + 1].type == PIPE || tokens[i + 1].arg == NULL)
		{
			tokens[i].next_token = NULL;
		}
		else
		{
			tokens[i].next_token = &tokens[i + 1];
		}
		i++;
	}
}

void ft_parser(t_token *tokens)
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
		else if (i == 0 || command_flag == 0)
		{
			tokens[i].type = COMMAND;
			command_flag = 1;
		}
		else
			tokens[i].type = FILE_NAME;

		i++;
	}
}

t_commandset *create_command_pipeline(t_token *tokens)
{
	t_commandset *commands;
	int num_of_commmands = count_commands(tokens);
	int i = 1;
	int j = 1;

	connect_tokens(tokens);
	commands = malloc(sizeof(t_commandset) * num_of_commmands + 1);
	commands[0].command = &tokens[0];

	while (tokens[i].arg != NULL)
	{
		if (tokens[i - 1].next_token == NULL && tokens[i].type != PIPE)
		{
			commands[j].command = &tokens[i];
			j++;
		}
		i++;
	}
	commands[j].command = NULL;
	return commands;
}

////////////////////////////ここからテスト関数など/////////////////////////////////

#include "token.h"
#include <stdio.h>

const char *TYPE_STRINGS[] = {
	"UNCATEGORIZED",
	"PIPE",			 // | (パイプ)
	"REDIRECT_OUT",	 // > (リダイレクト出力)
	"REDIRECT_IN",	 // < (リダイレクト入力)
	"APPEND_OUT",	 // >> (出力の追加)
	"HERE_DOCUMENT", // << (ヒアドキュメント)
	"COMMAND",
	"COMMAND_OPTION",
	"FILE_NAME"};

void test_parser(char *command)
{
	t_token *result;
	t_commandset *commands;
	result = ft_tokenizer(command);
	ft_parser(result);
	commands = create_command_pipeline(result);

	for (int i = 0; commands[i].command != NULL; i++)
	{
		printf("commands[%d].command->arg = [%s]\n", i, commands[i].command->arg);
	}
	puts("--------------------------------");
	for (int i = 0; result[i].arg != NULL; i++)
	{
		printf("arg: %-20s / ", result[i].arg);
		printf("type: [%s]\n", TYPE_STRINGS[result[i].type]);
		if (result[i].is_freed != 1)
		{
			free(result[i].arg);
			result[i].is_freed = 1;
		}
	}
	printf("\n");
	free(result);
	free(commands);
}

#include <libc.h>
int main()
{
	t_token *result;
	// t_commandset *commands;
	char *buff;
	while (1)
	{
		buff = readline("test here> ");
		// result = ft_tokenizer(buff);
		// ft_parser(result);
		// commands = create_command_pipeline(result);
		test_parser(buff);
		// for (int i = 0; result[i].arg != NULL; i++)
		// {
		// 	printf("arg: [%s]\n", result[i].arg);
		// 	printf("type: [%d]\n", result[i].type);
		// }
		free(buff);
	}
}
