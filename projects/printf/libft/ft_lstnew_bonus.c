/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:37:32 by aarmitan          #+#    #+#             */
/*   Updated: 2024/05/31 10:51:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nodes;

	nodes = (t_list *)malloc(sizeof(t_list));
	if (nodes == NULL)
		return (NULL);
	nodes->content = content;
	nodes->next = NULL;
	return (nodes);
}
