# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack.h"

int median(t_stack *a);
int find_min_val_offset(t_stack *st);
int aligmnent_cost(t_stack *a, t_stack *b, int offset, int execute);
void final_rotation(t_stack *a);

# endif // PUSH_SWAP_H