/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:09:12 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:35:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_correct_position(t_node *stack_b, int number)
{
	if (!stack_b)
		return (0);
	if (number < stack_b->value)
		return (0);
	while (stack_b->next)
	{
		if (stack_b->value < number && number < stack_b->next->value)
			return (1);
		stack_b = stack_b->next;
	}
	return (number > stack_b->value);
}
int	calculate_cost(t_node *stack_a, t_node *stack_b, int number)
{
	int	cost_a;
	int	cost_b;

	cost_a = 0;
	cost_b = 0;
	while (stack_a && stack_a->value != number)
	{
		stack_a = stack_a->next;
		cost_a++;
	}
	while (stack_b && !is_correct_position(stack_b, number))
	{
		stack_b = stack_b->next;
		cost_b++;
	}
	return (cost_a + cost_b);
}

int	find_cheapest_number(t_node *stack_a, t_node *stack_b)
{
	t_node	*current;
	int		min_cost;
	int		cheapest_number;
	int		cost;

	current = stack_a;
	min_cost = INT_MAX;
	cheapest_number = current->value;
	while (current)
	{
		cost = calculate_cost(stack_a, stack_b,
				current->value);
		if (cost < min_cost)
		{
			min_cost = cost;
			cheapest_number = current->value;
		}
		current = current->next;
	}
	return (cheapest_number);
}

void	push_cheapest_to_b(t_node **stack_a, t_node **stack_b)
{
	int	cheapest;

	cheapest = find_cheapest_number(*stack_a, *stack_b);
	while ((*stack_a)->value != cheapest)
	{
		if (calculate_cost(*stack_a, *stack_b, cheapest) > 0)
			ra(stack_a, 0);
		else
			rra(stack_a, 0);
	}
	pb(stack_a, stack_b, 0);
}
