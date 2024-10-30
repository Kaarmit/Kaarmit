/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:57 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:07:36 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"


t_stack	*fill_stack(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*new;
	long	n;
	int		i;
	int		error;

	stack_a = NULL;
	n = 0;
	i = 0;
	while (++i < argc)
	{
		n = ft_atoi(argv[i], &error);
		new = ft_lstnew_m(n);
		if (!new)
			ft_error(&stack_a, NULL, argc, argv);
		ft_lstadd_back_m(&stack_a, new);
	}
	return (stack_a);
}

void	index_stack(t_stack *stack_a, int size_a)
{
	t_stack	*current;
	t_stack	*node_max;
	int		value;

	while (--size_a > 0)
	{
		current = stack_a;
		value = INT_MIN;
		node_max = NULL;
		while (current)
		{
			if (current->data > value && !current->index)
			{
				value = current->data;
				node_max = current;
			}
			current = current->next;
		}
		if (node_max)
			node_max->index = size_a;
	}
}
