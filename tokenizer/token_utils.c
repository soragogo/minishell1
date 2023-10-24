/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:08:43 by emukamada         #+#    #+#             */
/*   Updated: 2023/10/20 00:03:31 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include <stdbool.h>
#include <libc.h>

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	is_dilimeter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}
