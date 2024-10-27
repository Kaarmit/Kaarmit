/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:32 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/27 11:03:31 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, chhar **av)
{
	t_node	*sa;
	t_node	*sb;
	int		str;
	char	**args;

	sa = NULL;
	sb = NULL;
	str = 0;
	if (ac < 2)
		return (0);
	if (ac == 2)
	{
		if (av[1][0] || !only_space(av[1]))
			error(&sa, &sb, av, str);
		args = ft_split(av[1], ' ');
		str = 1;
		if (!string_check(av[1]))
			return (free_all(&sa, &sb, args, str), 0);
	}
	else
		args = &argv[1];
	init_stack_a(&sa, &sb, args, str);
	if (!stack_sorted(&sa))
		sort_stack(&sa, &sb);
	return (free_all(&sa, &sb, arguments, string), 0);
}
