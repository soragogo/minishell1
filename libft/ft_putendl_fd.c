/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:18:32 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 16:14:56 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	long long int	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	while (len > 0)
	{
		write(fd, s, len);
		s += INT_MAX;
		len -= INT_MAX;
	}
	write(fd, "\n", 1);
}
