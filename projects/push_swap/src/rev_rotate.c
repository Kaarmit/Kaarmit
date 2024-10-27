/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:52:22 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 10:06:58 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void static	rev_rotate(t_node **stack)
{
	t_node	*cur;
	t_node	*begin;

	first = *stack;
	cur = *stack;
	while (cur->next->next)
		cur = cur->next;
	*stack = cur->next;
	cur->next->next = begin;
	cur->next = NULL;
}

void	rra(t_node **sa)
{
	ft_printf("rra\n");
	rev_rotate(sa);
}

void	rra(t_node **sb)
{
	ft_printf("rrb\n");
	rev_rotate(sb);
}

void	rrr(t_node **sa, t_node **sb)
{
	ft_printf("rrr\n");
	rev_rotate(sa);
	rev_rotate(sb);
}
