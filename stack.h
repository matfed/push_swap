# ifndef STACK_H
# define STACK_H

#include "util.h"

# define MAX_STACK_SIZE 600

typedef struct s_stack
{
    int	   *stack;
    int    max_size;
    int	   start;
    int    end;
}	t_stack;

void make_stack(t_stack *stack, int max_size);
void clear_stack(t_stack *stack);
void push(t_stack *stack, int value);
int pop(t_stack *stack);
void rot(t_stack *stack);
void rrot(t_stack *stack);
int seek(t_stack *stack);
int seek_offset(t_stack *stack, int offset);
int size(t_stack *stack);
int is_empty(t_stack *stack);
void swap(t_stack *stack);
void debug_stack(t_stack *stack);

# endif // STACK_H