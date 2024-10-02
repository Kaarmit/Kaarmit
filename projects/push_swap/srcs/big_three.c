/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_three.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:29:35 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 14:47:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// void	sort_three(t_node **stack_a)
// {
// 	if ((*stack_a)->value > (*stack_a)->next->value
// 		&& (*stack_a)->next->next->value > (*stack_a)->next->value)
// 		sa(stack_a, 0);
// 	else if ((*stack_a)->value < (*stack_a)->next->next->value
// 		&& (*stack_a)->next->value > (*stack_a)->next->next->value)
// 		rra(stack_a, 0);
// 	else
// 		ra(stack_a, 0);
// }
void	sort_three(t_node **stack_a)
{
 // Check if the stack is NULL or contains fewer than 3 nodes
	if (stack_a == NULL || *stack_a == NULL || (*stack_a)->next == NULL
		|| (*stack_a)->next->next == NULL)
	{
		// Handle the error (return or exit function, depending on your needs)
		return ; // or you can print an error message
	}
	// Now it's safe to access the values
	if ((*stack_a)->value > (*stack_a)->next->value
		&& (*stack_a)->next->value < (*stack_a)->next->next->value)
	{
		sa(stack_a, 0);
	}
	else if ((*stack_a)->value < (*stack_a)->next->next->value
		&& (*stack_a)->next->value > (*stack_a)->next->next->value)
	{
		rra(stack_a, 0);
	}
	else
	{
		ra(stack_a, 0);
	}
}
