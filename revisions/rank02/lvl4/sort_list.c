/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:58:44 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/09 18:18:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list *sort_list(t_list* lst, int (*cmp)(int, int))
{
	int	swap;
	t_list	start;

	start = lst;

	while (lst != NULL && lst->next != NULL)
	{
		if ((*cmp)(lst->data, lst->next->data) == 0)
		{
			swap = lst->data;
			lst->data = lst->next->data;
			lst->next->data = swap;
			lst = start;
		}
		else
			lst =lst->next;
	}
	return (start);
}
