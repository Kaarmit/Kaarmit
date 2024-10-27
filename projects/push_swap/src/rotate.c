/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:44:23 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 09:55:58 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void static	rotate(t_node **stack)
{
	t_node	*change;
	t_node	*cur;

	change = *stack;
	cur = *stack;
	*stack = change->next;
	while (cur->next)
			cur = cur->next;
		cur->next = change;
		change->next = NULL;
}

void	ra(t_node **sa)
{
	ft_printf("ra\n");
	rotate(sa);
}

void	rb(t_node **sb)
{
	ft_printf("rb\n");
	rotate(sb);
}

void	rr(t_node **a, t_node **sb)
{
	ft_printf("rr\n");
	rotate(sa);
	rotate(sb);
}
