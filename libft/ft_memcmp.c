/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:48:17 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/04 17:00:32 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	size_t			i;
	unsigned char	*buf1_;
	unsigned char	*buf2_;

	i = 0;
	buf1_ = (unsigned char *)buf1;
	buf2_ = (unsigned char *)buf2;
	while (i < n)
	{
		if (buf1_[i] != buf2_[i])
		{
			return (buf1_[i] - buf2_[i]);
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
//         char buf1[] = "\0abc\0de";      /* 途中に空文字のある文字列 */
//         char buf2[] = "\0abc\0de";
//         if (memcmp(buf1, buf2, 0) == 0)
//                 printf("buf1 = buf2\n");
//         else
//                 printf("buf1 != buf2\n");
//         if (memcmp(buf1, buf2, 0) == 0)
//                 printf("buf1 = buf2\n");
//         else
//                 printf("buf1 != buf2\n");
//         return 0;
// }
