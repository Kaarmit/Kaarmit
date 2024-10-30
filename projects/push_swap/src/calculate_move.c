/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:06:12 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:04:10 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	do_rr(t_stack **a, t_stack **b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(a, b);
	}
}

static void	do_rrr(t_stack **a, t_stack **b, int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(a, b);
	}
}

static void	do_rotate(t_stack **stack, int *cost, char stack_name)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			if (stack_name == 'a')
				ra(stack);
			else if (stack_name == 'b')
				rb(stack);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			if (stack_name == 'a')
				rra(stack);
			else if (stack_name == 'b')
				rrb(stack);
			(*cost)++;
		}
	}
}

void	cost_move(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current_a;
	t_stack	*current_b;
	int		size_a;
	int		size_b;

	current_a = *stack_a;
	current_b = *stack_b;
	size_a = ft_lstsize_m(current_a);
	size_b = ft_lstsize_m(current_b);
	while (current_b)
	{
		current_b->cost_b = current_b->position;
		if (current_b->position > size_b / 2)
			current_b->cost_b = (size_b - current_b->position) * -1;
		current_b->cost_a = current_b->sorted_position;
		if (current_b->sorted_position > size_a / 2)
			current_b->cost_a = (size_a - current_b->sorted_position) * -1;
		current_b = current_b->next;
	}
}

void	best_move(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*curnt_b;
	int		best;
	int		cost_a;
	int		cost_b;

	curnt_b = *stack_b;
	best = INT_MAX;
	while (curnt_b)
	{
		if (ft_abs(curnt_b->cost_a) + ft_abs(curnt_b->cost_b) < ft_abs(best))
		{
			best = ft_abs(curnt_b->cost_b) + ft_abs(curnt_b->cost_a);
			cost_a = curnt_b->cost_a;
			cost_b = curnt_b->cost_b;
		}
		curnt_b = curnt_b->next;
	}
	if (cost_a < 0 && cost_b < 0)
		do_rrr(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		do_rr(stack_a, stack_b, &cost_a, &cost_b);
	do_rotate(stack_a, &cost_a, 'a');
	do_rotate(stack_b, &cost_b, 'b');
	pa(stack_a, stack_b);
}
