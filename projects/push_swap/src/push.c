/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:59:22 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 10:06:55 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push(t_node **s_out, t_node **s_in)
{
	t_node	*change;

	change = *s_out;
	*s_out = change->next;
	change->next = *s_in;
	*s_in = change;
}


void	pb(t_node **sa, t_node **sb)
{
	if (!sa || !sb)
		return ;
	ft_printf("pb\n");
	push(sa, sb);
}

void	pa(t_node **sa, t_node **sb)
{
	if (!sa || !sb)
		return ;
	ft_printf("pa\n");
	push(sb, sa);
}
