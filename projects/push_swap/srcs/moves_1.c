/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:53:50 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/01 15:53:13 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	sa(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;

	if (*stack_a && (*stack_a)->next
		&& (*stack_a)->value > (*stack_a)->next->value)
	{
		// Perform swap if necessary
		first = *stack_a;
		second = (*stack_a)->next;
		first->next = second->next;
		second->next = first;
		*stack_a = second;
		return (1); // Swap occurred
	}
	return (0); // No swap
}

int	sb(t_node **stack_b)
{
	t_node	*first;
	t_node	*second;

	if (*stack_b && (*stack_b)->next
		&& (*stack_b)->value > (*stack_b)->next->value)
	{
		// Perform swap if necessary
		first = *stack_b;
		second = (*stack_b)->next;
		first->next = second->next;
		second->next = first;
		*stack_b = second;
		return (1); // Swap occurred
	}
	return (0); // No swap
}
void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a);
	sb(stack_b);
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_b;

	if (*stack_b)
	{
		top_b = *stack_b;
		*stack_b = (*stack_b)->next;
		top_b->next = *stack_a;
		*stack_a = top_b;
	}
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	if (*stack_a)
	{
		top_a = *stack_a;
		*stack_a = (*stack_a)->next;
		top_a->next = *stack_b;
		*stack_b = top_a;
	}
}
void	ra(t_node **stack_a)
{
	t_node	*first;
	t_node	*last;

	if (*stack_a && (*stack_a)->next)
	{
		first = *stack_a;
		last = *stack_a;
		while (last->next)
		{
			last = last->next;
		}
		*stack_a = first->next;
		first->next = NULL;
		last->next = first;
	}
}

void	rb(t_node **stack_b)
{
	t_node	*first;
	t_node	*last;

	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		last = *stack_b;
		while (last->next)
		{
			last = last->next;
		}
		*stack_b = first->next;
		first->next = NULL;
		last->next = first;
	}
}

RR

RRA

RRB

RRR 
