/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:48:21 by mayyamad          #+#    #+#             */
/*   Updated: 2023/10/03 16:14:58 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dst);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char		*s;
	size_t		len1;
	size_t		len2;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen_gnl(s1);
	if (s2 == NULL)
		return (NULL);
	len2 = ft_strlen_gnl(s2);
	s = (char *)malloc(len1 + len2 + 1);
	if (s == NULL)
		return (NULL);
	ft_memcpy_gnl(s, s1, len1);
	ft_memcpy_gnl(s + len1, s2, len2 + 1);
	free((void *)s1);
	return (s);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	const unsigned char	*p;

	if (!s)
		return (NULL);
	p = (const unsigned char *)s;
	while (*p != (unsigned char)c)
	{
		if (*p == '\0' && c != '\0')
			return (NULL);
		p++;
	}
	return ((char *)p);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
