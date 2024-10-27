/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:13 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 10:57:53 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_all(t_node **sa, t_node **sb, char **av, int str)
{
	free_stack(sa);
	free_stack(sb);
	if (str == 1)
	{
		free_split(av);
		av = NULL;
	}
}

void	free_stack(t_node **stack)
{
	t_node	*tmp;
	t_node	*cur;

	if (stack == NULL)
		return ;
	cur = *stack;
	while (cur)
	{
		tmp = cur->next;
		cur->nbr = 0;
		free(cur);
		cur = tmp;
	}
	*stack = NULL;
}

int	error(t_node **sa, t_node **sb, char **av, int str)
{
	write(2, "Error\n", 6);
	free_all(sa, sb, av, str);
	exit(1);
}

int	syntax_error(char *argument)
{
	int	i;

	i = 0;
	if (argument[i] == '+' || argument[i] == '-')
	{
		if (!(argument[i + 1] >= '0' && argument[i + 1] <= '9'))
			return (0);
		i++;
	}
	while (argument[i])
	{
		if (!(argument[i] >= '0' && argument[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	double_check(t_node *sa, int nbr)
{
	if (!sa)
		return (0);
	while (sa)
	{
		if (sa->nbr == nbr)
			return (1);
		sa = sa->next;
	}
	return (0);
}
