/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:18:13 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/03 16:19:48 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*index;
	t_list	*save;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	index = *lst;
	save = NULL;
	while (index != NULL)
	{
		save = index->next;
		index->next = NULL;
		del(index->content);
		free(index);
		index = save;
	}
	*lst = NULL;
}
