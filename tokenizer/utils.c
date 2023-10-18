/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:44 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/18 17:56:48 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/parser.h"
#include <stdbool.h>

int is_dilimeter(char c)
{
	return (c == '|' || c == '<' || c == '>') ? 1 : 0;
}

char *skip_spaces(char *str)
{
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    return str;
}
