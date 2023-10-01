/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:11:31 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/04 17:42:48 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*str;
	size_t		memory;

	if (count == 0 || size == 0)
		memory = 1;
	else
	{
		if (size * count / count != size)
			return (NULL);
		memory = size * count;
	}
	str = (void *)malloc(memory);
	if (str == NULL)
		return (NULL);
	return (ft_bzero(str, memory));
}

// int main(void)
// {
//    int *ptr,*p;
//    unsigned long i;

//    /* 500個のintサイズのメモリを確保 */
//    ptr = (int *)ft_calloc((size_t)SIZE_MAX / 10 + (size_t)1, 10);
//    if(ptr == NULL) {
//       printf("メモリが確保できません\n");
//       exit(EXIT_FAILURE);
//    }
//    printf("%lu", SIZE_MAX);
//    p = ptr;
//    for (i=0; i<18446744073709551615; i++) {
//       *p = i;
//       printf("%d ",*p);
//       p++;
//    }

//    /* メモリの開放 */
//    free(ptr);

//    return 0;
// }
