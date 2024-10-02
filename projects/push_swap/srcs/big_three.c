/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_three.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:29:35 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 12:33:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_node **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value
		&& (*stack_a)->next->next->value > (*stack_a)->next->value)
		sa(stack_a);
	else if ((*stack_a)->value < (*stack_a)->next->next->value
		&& (*stack_a)->next->value > (*stack_a)->next->next->value)
		rra(stack_a);
	else
		ra(stack_a);
}
