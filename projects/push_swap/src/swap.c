/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:02:32 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 10:07:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap(t_node **s)
{
	t_node	*begin;
	t_node	*second;

	begin = *s;
	second = begin->next;
	begin->next = second->next;
	second->next = begin;
	*stack = second;
}

void	sa(t_node **sa)
{
	ft_printf("sa\n");
	swap(sa);
}

void	sb(t_node **sb)
{
	ft_printf("sb\n");
	swap(sb);
}

void	ss(t_node **sa, t_node **sb)
{
	ft_printf("ss\n");
	swap(sa);
	swap(sb);
}
