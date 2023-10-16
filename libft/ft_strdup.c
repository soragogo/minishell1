/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:53 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/16 11:43:51 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*cpy;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	cpy = ft_calloc(i + 1, sizeof(char));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, str, i + 1);
	return (cpy);
}
