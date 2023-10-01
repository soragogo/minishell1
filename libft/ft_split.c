/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:45:13 by ekamada           #+#    #+#             */
/*   Updated: 2023/08/25 21:45:17 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:09:01 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 23:00:50 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_blocs(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		while (*s == c)
			s++;
	}
	return (count);
}

static char	**matrix_malloc(int count, int i, char **matrix)
{
	matrix[i] = malloc(sizeof(char) * (count + 1));
	if (matrix[i] == NULL)
	{
		while (i > 0)
			free(matrix[--i]);
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

static char	**matrix_maker(char const *s, char c, char **matrix)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (*s)
	{
		s += count;
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		count = 0;
		while (s[count] != c && s[count] != 0)
			count++;
		matrix = matrix_malloc(count, i, matrix);
		if (matrix == NULL)
			return (NULL);
		ft_strlcpy(matrix[i], s, count + 1);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;

	if (s == NULL)
		return (NULL);
	if (*s == 0)
	{
		matrix = (char **)malloc(sizeof(char *));
		matrix[0] = NULL;
		return (matrix);
	}
	if (c == 0)
	{
		matrix = malloc(sizeof(char *) * 2);
		if (matrix == NULL)
			return (NULL);
		*matrix = ft_strdup(s);
		*(matrix + 1) = NULL;
		return (matrix);
	}
	matrix = (char **)malloc(sizeof(char *) * (ft_count_blocs(s, c) + 1));
	if (matrix == NULL)
		return (NULL);
	return (matrix_maker(s, c, matrix));
}

// int main()
// {
// 	char *s = "tripouille";
// 	char c = 0;

// 	char **matrix = ft_split(s, c);
// 	for(int i = 0;matrix[i] != NULL; i++)
// 	{
// 		printf("%s\n", matrix[i]);
// 	}
// 	free(matrix);
// 	return 0;
// }
