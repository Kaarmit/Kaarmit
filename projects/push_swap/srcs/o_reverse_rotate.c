/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_reverse_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:09:18 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:28:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// rra: reverse rotate stack_a
void	rra(t_node **stack_a, int j)
{
	t_node *first, *last, *second_last;
	if (*stack_a && (*stack_a)->next)
	{
		first = *stack_a;
		last = *stack_a;
		while (last->next)
			last = last->next;
		second_last = *stack_a;
		while (second_last->next != last)
			second_last = second_last->next;
		second_last->next = NULL;
		last->next = first;
		*stack_a = last;
		if (j == 0)
			write(1, "rra\n", 4);
	}
}

// rrb: reverse rotate stack_b
void	rrb(t_node **stack_b, int j)
{
	t_node *first, *last, *second_last;
	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		last = *stack_b;
		while (last->next)
			last = last->next;
		second_last = *stack_b;
		while (second_last->next != last)
			second_last = second_last->next;
		second_last->next = NULL;
		last->next = first;
		*stack_b = last;
		if (j == 0)
			write(1, "rrb\n", 4);
	}
}

// rrr: reverse rotate both stack_a and stack_b
void	rrr(t_node **stack_a, t_node **stack_b, int j)
{
	rra(stack_a, 1);
	rrb(stack_b, 1);
	if (j == 0)
		write(1, "rrr\n", 4);
}
