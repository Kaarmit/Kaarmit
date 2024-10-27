#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}					t_node;

// pa: push top of stack_b to stack_a
void	pa(t_node **stack_a, t_node **stack_b, int j)
{
	t_node	*top_b;

	if (*stack_b)
	{
		top_b = *stack_b;
		*stack_b = (*stack_b)->next;
		top_b->next = *stack_a;
		*stack_a = top_b;
		if (j == 0)
			write(1, "pa\n", 3);
	}
}

// pb: push top of stack_a to stack_b
void	pb(t_node **stack_a, t_node **stack_b, int j)
{
	t_node	*top_a;

	if (*stack_a)
	{
		top_a = *stack_a;
		*stack_a = (*stack_a)->next;
		top_a->next = *stack_b;
		*stack_b = top_a;
		if (j == 0)
			write(1, "pb\n", 3);
	}
}

// rra: reverse rotate stack_a
void	rra(t_node **stack_a, int j)
{
	t_node *first, *last, *second_last;
	if (*stack_a && (*stack_a)->next)
	{
		first = *stack_a;
		last = *stack_a;
		while (last->next)
			last = last->next;
		second_last = *stack_a;
		while (second_last->next != last)
			second_last = second_last->next;
		second_last->next = NULL;
		last->next = first;
		*stack_a = last;
		if (j == 0)
			write(1, "rra\n", 4);
	}
}

// rrb: reverse rotate stack_b
void	rrb(t_node **stack_b, int j)
{
	t_node *first, *last, *second_last;
	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		last = *stack_b;
		while (last->next)
			last = last->next;
		second_last = *stack_b;
		while (second_last->next != last)
			second_last = second_last->next;
		second_last->next = NULL;
		last->next = first;
		*stack_b = last;
		if (j == 0)
			write(1, "rrb\n", 4);
	}
}

// rrr: reverse rotate both stack_a and stack_b
void	rrr(t_node **stack_a, t_node **stack_b, int j)
{
	rra(stack_a, 1);
	rrb(stack_b, 1);
	if (j == 0)
		write(1, "rrr\n", 4);
}
void	ra(t_node **stack_a, int j)
{
	t_node *first, *last;
	if (*stack_a && (*stack_a)->next)
	{
		first = *stack_a;
		last = *stack_a;
		while (last->next)
			last = last->next;
		*stack_a = first->next;
		first->next = NULL;
		last->next = first;
		if (j == 0)
			write(1, "ra\n", 3);
	}
}

// rb: rotate stack_b
void	rb(t_node **stack_b, int j)
{
	t_node *first, *last;
	if (*stack_b && (*stack_b)->next)
	{
		first = *stack_b;
		last = *stack_b;
		while (last->next)
			last = last->next;
		*stack_b = first->next;
		first->next = NULL;
		last->next = first;
		if (j == 0)
			write(1, "rb\n", 3);
	}
}

// rr: rotate both stack_a and stack_b
void	rr(t_node **stack_a, t_node **stack_b, int j)
{
	ra(stack_a, 1);
	rb(stack_b, 1);
	if (j == 0)
		write(1, "rr\n", 3);
}
int	sa(t_node **stack_a, int j)
{
	t_node *first, *second;
	if (*stack_a && (*stack_a)->next
		&& (*stack_a)->value > (*stack_a)->next->value)
	{
		first = *stack_a;
		second = (*stack_a)->next;
		first->next = second->next;
		second->next = first;
		*stack_a = second;
		if (j == 0)
			write(1, "sa\n", 3);
		return (1);
	}
	return (0);
}

// sb: swap the first two elements of stack_b
int	sb(t_node **stack_b, int j)
{
	t_node *first, *second;
	if (*stack_b && (*stack_b)->next
		&& (*stack_b)->value > (*stack_b)->next->value)
	{
		first = *stack_b;
		second = (*stack_b)->next;
		first->next = second->next;
		second->next = first;
		*stack_b = second;
		if (j == 0)
			write(1, "sb\n", 3);
		return (1);
	}
	return (0);
}

// ss: perform sa and sb at the same time
void	ss(t_node **stack_a, t_node **stack_b, int j)
{
	sa(stack_a, 1);
	sb(stack_b, 1);
	if (j == 0)
		write(1, "ss\n", 3);
}


int	is_correct_position(t_node *stack_b, int number)
{
	if (!stack_b)
		return (0);
	if (number < stack_b->value)
		return (0);
	while (stack_b->next)
	{
		if (*stack_b->value < number && number < stack_b->next->value)
			return (1);
		stack_b = stack_b->next;
	}
	return (number > stack_b->value);
}

int	calculate_cost(t_node *stack_a, t_node *stack_b, int number)
{
	int	cost_a;
	int	cost_b;

	cost_a = 0;
	cost_b = 0;
	while (stack_a && stack_a->value != number)
	{
		stack_a = stack_a->next;
		cost_a++;
	}
	while (stack_b && !is_correct_position(stack_b, number))
	{
		stack_b = stack_b->next;
		cost_b++;
	}
	return (cost_a + cost_b);
}

int	find_cheapest_number(t_node *stack_a, t_node *stack_b)
{
	t_node	*current;
	int		min_cost;
	int		cheapest_number;
	int		cost;

	current = stack_a;
	min_cost = INT_MAX;
	cheapest_number = current->value;
	while (current)
	{
		cost = calculate_cost(stack_a, stack_b,
				current->value);
	       	if (cost M min_cost)
		{
			min_cost = cost;
			cheapest_number = current->value;
		}
		current = current->next;
	}
	return (cheapest_number);
}

void	push_cheapest_to_b(t_node **stack_a, t_node **stack_b)
{
	int	cheapest;

	cheapest = find_cheapest_number(*stack_a, *stack_b);
	while ((*stack_a)->value != cheapest)
	{
		if (calculate_cost(*stack_a, *stack_b, cheapest) > 0)
			ra(stack_a);
		else
			rra(stack_a);
	}
	pb(stack_a, stack_b);
}
void	sort_three(t_node **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value
		&& (*stack_a)->next->next->value > (*stack_a)->next->value)
		sa(stack_a);
	else if ((*stack_a)->value < (*stack_a)->next->next->value
		&& (*stack_a)->next->value > (*stack_a)->next->next->value)
		rra(stack_a);
	else
		ra(stack_a);
}
void	push_back_to_a(t_node **stack _a, t_node **stack_b)
{
	while (*stack_b)
		pa(stack_a, stack_b);
}
void	final_sort(t_node **stack_a)
{
	t_node	*min_node;
	int		min_val;

	min_node = *stack_a;
	min_val = min_node->value;
	while (min_node)
	{
		if (min_node->value < min_val)
			min_val = min_node->value;
		min_node = min_node->next;
	}
	while ((*stack_a)->value != min_val)
		ra(stack_a);
}

void	turk_algorithm(t_node **stack_a, t_node **stack_b)
{
	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	while (stack_size(*stack_a) > 3)
		push_cheapest_to_b(stack_a, stack_b);
	sort_three(stack_a);
	push_back_to_a(stack_a, stack_b);
	final_sort(stack_a);
}

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

