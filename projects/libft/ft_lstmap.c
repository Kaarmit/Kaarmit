/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:21 by aarmitan          #+#    #+#             */
/*   Updated: 2024/05/31 15:55:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;

	{
		if (!lst || !f || !del)
			return (0);
		new_list = ft_lstnew(f(lst->content));
		if (!new_list)
			return (0);
		save = new_list;
		lst = lst->next;
		while (lst)
		{
			new_list->next = ft_lstnew(f(lst->content));
			if (!new_list->next)
			{
				ft_lstclear(&save, del);
				return (0);
			}
			new_list = new_list->next;
			lst = lst->next;
		}
		new_list->next = 0;
		return (save);
	}
}
