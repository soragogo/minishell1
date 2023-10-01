/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:32 by ekamada           #+#    #+#             */
/*   Updated: 2023/09/27 19:23:07 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

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

void test_commandsets(t_commandset *commandsets, int num_of_commands)
{
	char **cmd;

	for (int i = 0; i < num_of_commands; i++)
	{
		printf("---------------commandsets[%d]--------------------\n", i);
		cmd = commandsets[i].command;
		puts("① commands\n");
		while (*cmd)
		{
			printf("%s\n", *cmd);
			cmd++;
		}
		puts("② nodes");
		for (int j = 0; j < 1024; j++)
		{
			if (commandsets[i].node[j].filename == NULL)
				break;
			printf("redirection_type: %d ", commandsets[i].node[j].type);
			printf("redirection_filename: %s\n", commandsets[i].node[j].filename);
			if (commandsets[i].node[j].next == NULL)
				break;
		}
	}
}
