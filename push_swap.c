#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

void make_stack(t_stack *stack, int max_size)
{
    stack->stack = (int *)malloc(sizeof(int) * max_size);
    stack->max_size = max_size;
    stack->start = 0;
    stack->end = 0;
}

void clear_stack(t_stack *stack)
{
    free(stack->stack);
    stack->max_size = 0;
    stack->start = 0;
    stack->end = 0;
}

void push(t_stack *stack, int value)
{
    stack->stack[stack->end] = value;
    stack->end = (stack->end + 1) % stack->max_size;
    if (stack->end == stack->start) {
        debug("Error: stack is full\n");
        exit(1);
    }
}

int pop(t_stack *stack)
{
    if (stack->start == stack->end) {
        debug("Error: stack is empty\n");
        exit(1);
    }
    
    stack->end = stack->end - 1;
    if (stack->end < 0)
        stack->end = stack->max_size - 1;
    return (stack->stack[stack->end]);
}

int seek(t_stack *stack)
{
    int end = stack->end - 1;
    if (end < 0)
        end = stack->max_size - 1;
    return (stack->stack[end]);
}

int seek_offset(t_stack *stack, int offset)
{
    if (offset >= 0) {
        int end = stack->end - 1 - offset;
        if (end < 0)
            end = stack->max_size + end;
        return (stack->stack[end]);
    } else {
        int start = stack->start + offset - 1;
        if (start >= stack->max_size)
            start = start - stack->max_size;
        return (stack->stack[start]);
    }
}

void rot(t_stack *stack)
{
    int tmp = pop(stack);
    stack->start = stack->start - 1;
    if (stack->start < 0)
        stack->start = stack->max_size - 1;
    stack->stack[stack->start] = tmp;
}

void rrot(t_stack *stack)
{
    int tmp = stack->stack[stack->start];
    stack->start = (stack->start + 1) % stack->max_size;
    push(stack, tmp);
}

int is_empty(t_stack *stack)
{
    return (stack->start == stack->end);
}

void swap(t_stack *stack)
{
    int v1 = pop(stack);
    int v2 = pop(stack);
    push(stack, v1);
    push(stack, v2);
}

void debug_stack(t_stack *stack)
{
    for (int i = stack->start; i != stack->end; i = (i + 1) % stack->max_size) {
        debug("%d ", stack->stack[i]);
    }
    debug("\n");
}