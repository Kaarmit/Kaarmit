/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:32 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/30 16:05:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_sorting_method(t_stack **stack_a, t_stack **stack_b, int size_a)
{
	if (size_a < 3 && !sorted(*stack_a))
		sa(stack_a);
	else if (size_a == 3 && !sorted(*stack_a))
		sort_three(stack_a);
	else if (size_a > 3 && !sorted(*stack_a))
		hybrid_sort(stack_a, stack_b, size_a);
}

// When arguments are passed as a single string

static char	**ft_args(char **argv)
{
	char	*argv0;
	char	*tmp;
	char	**args;

	argv0 = ft_strjoin(argv[0], " ");
	if (!argv0)
		ft_error(NULL, NULL, 2, NULL);
	tmp = ft_strjoin(argv0, argv[1]);
	free(argv0);
	if (!tmp)
		ft_error(NULL, NULL, 2, NULL);
	args = ft_split(tmp, ' ');
	free(tmp);
	if (!args)
		ft_error(NULL, NULL, 2, NULL);
	return (args);
}

static int	ft_argslen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	size_t	size_a;

	if (argc < 2)
		return (0);
	if (argc == 2)
		argv = ft_args(argv);
	if (!check_data(argv))
		ft_error(NULL, NULL, argc, argv);
	stack_b = NULL;
	if (argc == 2)
		stack_a = fill_stack(ft_argslen(argv), argv);
	else
		stack_a = fill_stack(argc, argv);
	size_a = ft_lstsize_m(stack_a);
	index_stack(stack_a, size_a + 1);
	ft_sorting_method(&stack_a, &stack_b, size_a);
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	if (argc == 2)
		ft_free_split(&argv);
	return (0);
}
