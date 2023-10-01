/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:04 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 14:52:29 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int				i;
	unsigned char	*dst1;
	unsigned char	*src1;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return ((void *)dst1);
}

// int main(void)
// {
//     int a = 10;
//     int b;

//     int src1[10] = {
// 		1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int dst1[10];

//     char src2[10] = ":)";
//     char dst2[10] = "hello";

//     int i;
//     ft_memcpy(&b, &a, sizeof(int));
//     printf("%d\n", b);

//     ft_memcpy(dst1, src1, sizeof(int) * 10);

//     for (i = 0; i < 10; i++)
//     {
//         printf("%d\n", dst1[i]);
//     }

//     ft_memcpy(dst2, src2, sizeof(char) * 2);
//     printf("%s", dst2);
// }
