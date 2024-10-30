/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:59:22 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:05:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	position(t_stack **stack)
{
	t_stack	*current;
	int		i;

	current = *stack;
	i = 0;
	while (current)
	{
		current->position = i++;
		current = current->next;
	}
}

static int	best_position(t_stack **stack_a, int ref_index, int sorted_index)
{
	t_stack	*current_a;
	int		optimal_position;

	optimal_position = -1;
	current_a = *stack_a;
	while (current_a)
	{
		if (current_a->index > ref_index && current_a->index < sorted_index)
		{
			sorted_index = current_a->index;
			optimal_position = current_a->position;
		}
		current_a = current_a->next;
	}
	return (optimal_position);
}

static int	sorted_pos(t_stack **stack_a, t_stack *current_b, int sorted_index)
{
	int	optimal_position;

	optimal_position = best_position(stack_a, current_b->index, sorted_index);
	if (optimal_position != -1)
		return (optimal_position);
	return (best_position(stack_a, -1, sorted_index));
}

void	sorted_positions(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current_b;

	current_b = *stack_b;
	position(stack_a);
	position(stack_b);
	while (current_b)
	{
		current_b->sorted_position = sorted_pos(stack_a, current_b, INT_MAX);
		current_b = current_b->next;
	}
}
