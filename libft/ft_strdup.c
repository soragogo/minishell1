/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:53 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 21:49:47 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*cpy;

	i = ft_strlen(str);
	cpy = malloc(sizeof(char) * i + 1);
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, str, i + 1);
	return (cpy);
}

// int main()
// {
// 	char *str = "Hello People";
// 	char *cpy = ft_strdup(str);
// 	printf("Copied string: %s\n", cpy);
// 	free(cpy);
// 	return 0;
// }
