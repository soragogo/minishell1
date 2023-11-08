/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:18:34 by ekamada           #+#    #+#             */
/*   Updated: 2023/11/08 09:59:20 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
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
}
