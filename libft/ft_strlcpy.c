/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:40:54 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 15:31:25 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	if (dstsize == 0)
		return (ft_strlen(src));
	count = ft_strlen(src);
	while (dstsize > 1 && *src)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = 0;
	return (count);
}

// int main()
// {

// 	char src[] = "coucou";
// 	char dest[10]; memset(dest, 'A', 10);
// 	ft_strlcpy(dest, src, 0);
// 	printf("%s", dest);
// }