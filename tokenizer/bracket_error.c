/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:51 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/31 14:50:44 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include <stdbool.h>
#include <libc.h>

int	is_mismatched_bracket(char c, char l_br, char r_br, bool *in_br)
{
	if (c == l_br)
	{
		if (*in_br)
			return (1);
		*in_br = true;
	}
	else if (c == r_br)
	{
		if (!(*in_br))
			return (1);
		*in_br = false;
	}
	return (0);
}

int	bracket_error(t_token *tokens, char l_br, char r_br)
{
	int		i;
	int		j;
	bool	in_br;
	bool	in_quote;

	in_br = false;
	in_quote = false;
	i = 0;
	while (tokens[i].arg)
	{
		j = 0;
		while (tokens[i].arg[j])
		{
			if (tokens[i].arg[j] == '\"')
				in_quote = !in_quote;
			if (!in_quote)
			{
				if (is_mismatched_bracket(tokens[i].arg[j], l_br, r_br, &in_br))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (in_br);
}
