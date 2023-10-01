/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:32 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/26 21:24:46 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(const char *str, int minus, size_t count)
{
	char	*str_;

	str_ = (char *)str;
	if (count > ft_strlen("9223372036854775807"))
		return (-1);
	else if (count == ft_strlen("9223372036854775807"))
	{
		if (minus < 0)
		{
			if ((ft_strncmp(str_, "9223372036854775808", 19)) > 0)
				return (0);
		}
		else if ((ft_strncmp(str_, "9223372036854775807", 19)) > 0)
			return (-1);
	}
	return (1);
}

static size_t	num_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

static long long int	num_maker(const char *str)
{
	long long int	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int		minus;
	size_t	count;

	count = 0;
	minus = 1;
	while ((*str == '\t') || (*str == '\n') || (*str == '\v')
		|| (*str == '\f') || (*str == '\r') || (*str == ' '))
		str++;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	count = num_len(str);
	if (check_overflow(str, minus, count) != 1)
		return (check_overflow(str, minus, count));
	return ((int)num_maker(str) * minus);
}
// int main()
// {
// 	printf("%d", ft_atoi("18446744073709551614"));
// }
