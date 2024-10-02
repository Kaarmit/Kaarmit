#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}					t_node;

// Functions

void	final_sort(t_node **stack_a);
void	turk_algorithm(t_node **stack_a, t_node **stack_b);
void	push_back_to_a(t_node **stack_a, t_node **stack_b);
void	sort_three(t_node **stack_a);
void	push_cheapest_to_b(t_node **stack_a, t_node **stack_b);
void	append_node(t_node **stack, int value);
void	pa(t_node **stack_a, t_node **stack_b, int j);
void	pb(t_node **stack_a, t_node **stack_b, int j);
void	rra(t_node **stack_a, int j);
void	rrb(t_node **stack_b, int j);
void	rrr(t_node **stack_a, t_node **stack_b, int j);
void	ra(t_node **stack_a, int j);
void	rb(t_node **stack_b, int j);
void	rr(t_node **stack_a, t_node **stack_b, int j);
void	ss(t_node **stack_a, t_node **stack_b, int j);
int	is_correct_position(t_node *stack_b, int number);
int	calculate_cost(t_node *stack_a, t_node *stack_b, int number);
int	find_cheapest_number(t_node *stack_a, t_node *stack_b);
int	stack_size(t_node *stack);
int	main(int argc, char **argv);
int	sa(t_node **stack_a, int j);
int	sb(t_node **stack_b, int j);
t_node	*new_node(int value);
