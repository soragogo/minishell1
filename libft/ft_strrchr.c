/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:39:56 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 16:15:06 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	else if (last == -1)
		return (NULL);
	else
		return ((char *)s + last);
}

/*
int main()
{
	char str[] = "abbdefghijklmnopqrstuvwxyzb", *p;
	p = ft_strrchr(str, 'b');
	printf("%ld", p - str);
	return 0;
}
*/
