/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:19 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 11:08:49 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stack_a(t_node **sa, t_node **sb, char **av, int str)
{
	long	n;
	int		i;

	i = 0;
	while (av[i])
	{
		if (!syntax_error(av[i]))
			error(sa, sb, av, str);
		n = atol(av[i]);
		if (n > INT_MAX || n < INT_MIN)
			error(sa, sb, av, str);
		if (double_check(*sa, (int)n) == 1)
			error(sa, sb, av, str);
		make_node(sa, (int)n);
		i++;
	}
}

void	make_node(t_node **stack, int n)
{
	t_node *node;
	t_node *cur;

	if (!stack)
		return;
	node = malloc(sizeof(t_node));
	if (!node)
		return;
	node->next = NULL;
	node->nbr = n;
	if (*stack == NULL)
		*stack = node;
	else
	{
		cur = *stack;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
}

int	stack_sorted(t_node	**stack)
{
	t_node	*cur;

	if (!stack)
		return (1);
	cur = *stack;
	while (cur->nbr < cur->next->nbr)
	{
		if (cur->next->next == NULL)
			return (1);
		cur = cur->next;
	}
	return (0);
}
