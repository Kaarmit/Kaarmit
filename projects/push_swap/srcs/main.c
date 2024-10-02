/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:39:06 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/02 13:54:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.c"

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		value;
	t_node	*current;
	t_node	*temp;
	t_node	*temp;

	stack_a = NULL;
	stack_b = NULL;
	// Check for the correct number of arguments
	if (argc < 2)
	{
		write(2, "Error: At least one number is required\n", 39);
		return (1);
	}
	// Parse command-line arguments and fill stack_a
	for (int i = 1; i < argc; i++)
	{
		value = atoi(argv[i]);
		append_node(&stack_a, value);
	}
	// Call the sorting algorithm
	turk_algorithm(&stack_a, &stack_b);
	// Optionally: Print the sorted stack_a
	current = stack_a;
	while (current)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
	// Free allocated memory (add a function for this if needed)
	while (stack_a)
	{
		temp = stack_a;
		stack_a = stack_a->next;
		free(temp);
	}
	while (stack_b)
	{
		temp = stack_b;
		stack_b = stack_b->next;
		free(temp);
	}
	return (0);
}
