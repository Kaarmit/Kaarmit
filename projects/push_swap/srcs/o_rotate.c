/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:09:08 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:28:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_node **stack_a, int j)
{
	t_node *first, *last;
	if (*stack_a && (*stack_a)->next)
	{
		first = *stack_a;
		last = *stack_a;
		while (last->next)
			last = last->next;
		*stack_a = first->next;
		first->next = NULL;
		last->next = first;
		if (j == 0)
			write(1, "ra\n", 3);
	}
}

// rb: rotate stack_b
void	rb(t_node **stack_b, int j)
{
	t_node *first, *last;
	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		last = *stack_b;
		while (last->next)
			last = last->next;
		*stack_b = first->next;
		first->next = NULL;
		last->next = first;
		if (j == 0)
			write(1, "rb\n", 3);
	}
}

// rr: rotate both stack_a and stack_b
void	rr(t_node **stack_a, t_node **stack_b, int j)
{
	ra(stack_a, 1);
	rb(stack_b, 1);
	if (j == 0)
		write(1, "rr\n", 3);
}
