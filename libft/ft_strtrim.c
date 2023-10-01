/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:43:00 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 17:41:10 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cpymaker(char const *s1, char const *set, int set_len, int check)
{
	char	*cpy;
	char	*s1_;

	s1_ = (char *)s1;
	while (*(s1_ + 1))
		s1_++;
	while (*s1_)
	{
		while (*set)
		{
			if (*s1_ == *set)
				check = 0;
			set++;
		}
		if (check == 1)
			break ;
		check = 1;
		s1_--;
		set -= set_len;
	}
	cpy = malloc(sizeof(char) * (s1_ - s1 + 2));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s1, s1_ - s1 + 2);
	return (cpy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		set_len;
	int		check;

	check = 1;
	set_len = ft_strlen(set);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1)
	{
		while (*set)
		{
			if (*s1 == *set)
				check = 0;
			set++;
		}
		if (check == 1)
			break ;
		check = 1;
		s1++;
		set -= set_len;
	}
	if (*set == 0)
		set -= set_len;
	check = 1;
	return (cpymaker(s1, set, set_len, check));
}

// int main()
// {
// 	char s1[] = "Hello world";
// 	char set[] = "world";
// 	char *s2 = ft_strtrim(s1, set);

// 	// printf("%s", s2);
// 	free(s2);
// 	return 0;
// }