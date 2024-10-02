/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:53:50 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:28:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// sa: swap the first two elements of stack_a
int	sa(t_node **stack_a, int j)
{
	t_node *first, *second;
	if (*stack_a && (*stack_a)->next
		&& (*stack_a)->value > (*stack_a)->next->value)
	{
		first = *stack_a;
		second = (*stack_a)->next;
		first->next = second->next;
		second->next = first;
		*stack_a = second;
		if (j == 0)
			write(1, "sa\n", 3);
		return (1);
	}
	return (0);
}

// sb: swap the first two elements of stack_b
int	sb(t_node **stack_b, int j)
{
	t_node *first, *second;
	if (*stack_b && (*stack_b)->next
		&& (*stack_b)->value > (*stack_b)->next->value)
	{
		first = *stack_b;
		second = (*stack_b)->next;
		first->next = second->next;
		second->next = first;
		*stack_b = second;
		if (j == 0)
			write(1, "sb\n", 3);
		return (1);
	}
	return (0);
}

// ss: perform sa and sb at the same time
void	ss(t_node **stack_a, t_node **stack_b, int j)
{
	sa(stack_a, 1);
	sb(stack_b, 1);
	if (j == 0)
		write(1, "ss\n", 3);
}



// ra: rotate stack_a



