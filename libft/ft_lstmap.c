/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekamada <ekamada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:18:18 by ekamada           #+#    #+#             */
/*   Updated: 2023/06/04 16:44:54 by ekamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{	
	void	*new_content;
	t_list	*new;
	t_list	*lst_new;
	t_list	*lst_last;

	lst_new = NULL;
	lst_last = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (new == NULL)
		{
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		if (lst_new == NULL)
			lst_new = new;
		else
			lst_last->next = new;
		lst_last = new;
		lst = lst->next;
	}
	return (lst_new);
}
