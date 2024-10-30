/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:52:22 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:05:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"


int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

void	ft_free_split(char ***s)
{
	int	i;

	if (!s || !*s)
		return ;
	i = -1;
	while ((*s)[++i])
	{
		free((*s)[i]);
		(*s)[i] = NULL;
	}
	free(*s);
	*s = NULL;
}

void	ft_error(t_stack **stack_a, t_stack **stack_b, int argc, char **argv)
{
	if (stack_a && *stack_a)
		ft_free_stack(stack_a);
	if (stack_b && *stack_b)
		ft_free_stack(stack_b);
	if (argv && argc == 2)
		ft_free_split(&argv);
	ft_putendl_fd("Error", 2);
	exit (EXIT_FAILURE);
}
