/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:39:55 by ekamada           #+#    #+#             */
/*   Updated: 2023/10/16 11:29:05 by emukamada        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		strslen;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	strslen = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)ft_calloc(strslen + 1, sizeof(char));
	if (joined == NULL)
		return (NULL);
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	return (joined);
}

// #include <stdio.h>
// int main()
// {
//         char *s1 = "1111";
//         char *s2 = "2222";
//         char *s3 = "3333";
//         char *s4 = "4444";
//         char *s[]  = {s1, s2, s3, s4};
//         char sep[] = "ABCD";
//         char *result = ft_strjoin(4, s, sep);
//         printf("%s\n", result);
//         free (result);
//         return(0);
// }
