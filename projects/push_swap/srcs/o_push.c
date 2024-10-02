/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_push.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:09:27 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:28:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// pa: push top of stack_b to stack_a
void	pa(t_node **stack_a, t_node **stack_b, int j)
{
	t_node	*top_b;

	if (*stack_b)
	{
		top_b = *stack_b;
		*stack_b = (*stack_b)->next;
		top_b->next = *stack_a;
		*stack_a = top_b;
		if (j == 0)
			write(1, "pa\n", 3);
	}
}

// pb: push top of stack_a to stack_b
void	pb(t_node **stack_a, t_node **stack_b, int j)
{
	t_node	*top_a;

	if (*stack_a)
	{
		top_a = *stack_a;
		*stack_a = (*stack_a)->next;
		top_a->next = *stack_b;
		*stack_b = top_a;
		if (j == 0)
			write(1, "pb\n", 3);
	}
}
