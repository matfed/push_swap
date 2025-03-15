# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define MAX_SIZE 600

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
int is_empty(t_stack *stack);
void debug_stack(t_stack *stack);

# ifdef DEBUG
# define debug(...) printf(__VA_ARGS__)
# else
# define debug(...)
# endif

# endif // PUSH_SWAP_H