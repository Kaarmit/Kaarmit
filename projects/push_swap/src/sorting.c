/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:06:04 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:07:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	sorted(t_stack *stack)
{
	if (!stack || !stack->next)
		return (1);
	while (stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	sort_three(t_stack **stack)
{
	t_stack	*current;
	int		index_max;

	current = *stack;
	index_max = current->index;
	while (current)
	{
		if (current->index > index_max)
			index_max = current->index;
		current = current->next;
	}
	if ((*stack)->index == index_max)
		ra(stack);
	else if ((*stack)->next->index == index_max)
		rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}

static void	ft_pb_but_three(t_stack **stack_a, t_stack **stack_b, int size_a)
{
	int	in_stack_b;
	int	i;

	in_stack_b = 0;
	i = -1;
	while (++i < size_a && size_a > 6 && in_stack_b < size_a / 2)
	{
		if ((*stack_a)->index < size_a / 2)
			ra(stack_a);
		else
		{
			pb(stack_a, stack_b);
			in_stack_b++;
		}
	}
	in_stack_b--;
	while (++in_stack_b < size_a - 3)
		pb(stack_a, stack_b);
}

static void	ft_index_min_top(t_stack **stack_a, int size_a)
{
	t_stack	*current;
	int		index_min;
	int		index_min_pos;

	current = *stack_a;
	index_min = INT_MAX;
	index_min_pos = 0;
	position(stack_a);
	while (current)
	{
		if (current->index < index_min)
		{
			index_min = current->index;
			index_min_pos = current->position;
		}
		current = current->next;
	}
	if (index_min_pos <= size_a / 2)
		while (index_min_pos-- > 0)
			ra(stack_a);
	else
		while (index_min_pos++ < size_a)
			rra(stack_a);
}

void	hybrid_sort(t_stack **stack_a, t_stack **stack_b, int size_a)
{
	ft_pb_but_three(stack_a, stack_b, size_a);
	sort_three(stack_a);
	while (*stack_b)
	{
		sorted_positions(stack_a, stack_b);
		cost_move(stack_a, stack_b);
		best_move(stack_a, stack_b);
	}
	if (!sorted(*stack_a))
		ft_index_min_top(stack_a, size_a);
}
