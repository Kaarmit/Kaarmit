/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:53:50 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 13:54:13 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// Stack size function (you might need to implement this)
int	stack_size(t_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

// Function to create a new node
t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		write(2, "Memory allocation error\n", 24);
		exit(EXIT_FAILURE);
	}
	node->value = value;
	node->next = NULL;
	return (node);
}

// Function to append a new node to the stack
void	append_node(t_node **stack, int value)
{
	t_node	*new;
	t_node	*temp;

	new = new_node(value);
	if (!*stack)
	{
		*stack = new;
	}
	else
	{
		temp = *stack;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}
