

#include "parser.h"
#include <stdbool.h>
#include <libc.h>

int count_redirection(t_token *tokens, int current_pipe)
{
    int i = 0;
    int count = 0;

    while (tokens[i].arg && current_pipe)
    {
        if (tokens[i++].type == PIPE)
			current_pipe--;
    }
    if (tokens[i].type == PIPE) i++;
    while (tokens[i].arg && tokens[i].type != PIPE)
    {
        if (tokens[i].type >= REDIRECT_OUT && tokens[i].type <= HERE_DOCUMENT)
            count++;
        i++;
    }
    return (count);
}


void connect_redirections(t_redirect *node, int count)
{
	if (count <= 0)
		return;
	node[0].prev = NULL;
	node[0].next = (count > 1) ? &node[1] : NULL;
	for (int i = 1; i < count - 1; i++)
	{
		node[i].prev = &node[i - 1];
		node[i].next = &node[i + 1];
	}
	if (count > 1)
	{
		node[count - 1].prev = &node[count - 2];
		node[count - 1].next = NULL;
	}
}

void import_redirection(t_token *tokens, t_commandset *commandsets, int num_of_commands)
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
		count = count_redirection(tokens, i);
		if (count == 0)
		{
			commandsets[i].node = NULL;
			i++;
			// return ;
			continue ;
		}
		commandsets[i].node = ft_calloc(count, sizeof(t_redirect));
		connect_redirections(commandsets[i].node, count);

		while (tokens[j].arg && tokens[j].type != PIPE)
		{
			if (tokens[j].type >= REDIRECT_OUT && tokens[j].type <= HERE_DOCUMENT && tokens[j + 1].type == FILE_NAME)
			{
				commandsets[i].node[k].type = tokens[j].type;
				commandsets[i].node[k++].filename = ft_strdup(tokens[++j].arg);
			}
			j++;
		}

		if (tokens[j].type == PIPE && tokens[j + 1].arg) j++;
		i++;
		k = 0;
	}
}

