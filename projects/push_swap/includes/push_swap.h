#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>
#include <limits.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/get_next_line.h"


// STACK STRUCTURE
typedef struct s_stack
{
	int				data;
	int				index;
	int				position;
	int				sorted_position;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

// DATA CHECK
int		check_data(char **argv);

// OPERATIONS
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);

// STACK
t_stack	*ft_lstnew_m(int value);
void	ft_lstadd_back_m(t_stack **lst, t_stack *new);
size_t	ft_lstsize_m(t_stack *lst);
t_stack	*ft_lstlast_m(t_stack *lst);
t_stack	*ft_lstsecondlast(t_stack *stack);
t_stack	*fill_stack(int argc, char **argv);
void	index_stack(t_stack *stack_a, int stack_size);

// SORTING ALGORITHMS
int		sorted(t_stack *stack);
void	sort_three(t_stack **stack_a);
void	hybrid_sort(t_stack **stack_a, t_stack **stack_b, int size_a);

// POSITION
void	position(t_stack **stack);
void	sorted_positions(t_stack **a, t_stack **b);

// CALCULATE MOVE
void	cost_move(t_stack **stack_a, t_stack **stack_b);
void	best_move(t_stack **stack_a, t_stack **stack_b);

// UTILS
int		ft_abs(int n);
void	ft_free_stack(t_stack **stack);
void	ft_free_split(char ***s);
void	ft_error(t_stack **stack_a, t_stack **stack_b, int argc, char **argv);

#endif

