/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:36:45 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:13:26 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	final_sort(t_node **stack_a)
{
	t_node	*min_node;
	int		min_val;

	min_node = *stack_a;
	min_val = min_node->value;
	while (min_node)
	{
		if (min_node->value < min_val)
			min_val = min_node->value;
		min_node = min_node->next;
	}
	while ((*stack_a)->value != min_val)
		ra(stack_a);
}

void	turk_algorithm(t_node **stack_a, t_node **stack_b)
{
	pb(stack_a, stack_b, 0);
	pb(stack_a, stack_b, 0);
	while (stack_size(*stack_a) > 3)
		push_cheapest_to_b(stack_a, stack_b);
	sort_three(stack_a);
	push_back_to_a(stack_a, stack_b);
	final_sort(stack_a, 1);
}
