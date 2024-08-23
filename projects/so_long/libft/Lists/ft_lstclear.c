/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:58:40 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 15:41:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	{
		if (*lst == 0)
			return ;
		while (*lst)
		{
			next = (*lst)->next;
			if (del)
				del((*lst)->content);
			free(*lst);
			*lst = next;
		}
		*lst = 0;
	}
}
