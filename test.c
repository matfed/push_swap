#include <stdio.h>
#include <assert.h>
#include "push_swap.h"

void test_make_stack() {
    t_stack stack;
    make_stack(&stack, 10);
    printf("stack.max_size = %d\n", stack.max_size);
    printf("stack.start = %d\n", stack.start);
    printf("stack.end = %d\n", stack.end);
    for (int i = 0; i < stack.max_size; i++) {
        printf("stack.stack[%d] = %d\n", i, stack.stack[i]);
    }
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 4);
    push(&stack, 5);
    push(&stack, 6);
    printf("stack.max_size = %d\n", stack.max_size);
    printf("stack.start = %d\n", stack.start);
    printf("stack.end = %d\n", stack.end);
    for (int i = 0; i < stack.max_size; i++) {
        printf("stack.stack[%d] = %d\n", i, stack.stack[i]);
    }
    rot(&stack);
    rot(&stack);
    rot(&stack);
    printf("stack.max_size = %d\n", stack.max_size);
    printf("stack.start = %d\n", stack.start);
    printf("stack.end = %d\n", stack.end);
    for (int i = 0; i < stack.max_size; i++) {
        printf("stack.stack[%d] = %d\n", i, stack.stack[i]);
    }
    rot(&stack);
    rot(&stack);
    rot(&stack);
    printf("stack.max_size = %d\n", stack.max_size);
    printf("stack.start = %d\n", stack.start);
    printf("stack.end = %d\n", stack.end);
    for (int i = 0; i < stack.max_size; i++) {
        printf("stack.stack[%d] = %d\n", i, stack.stack[i]);
    }
    assert(pop(&stack) == 6);
    assert(pop(&stack) == 5);
    assert(pop(&stack) == 4);
    assert(pop(&stack) == 3);
    assert(pop(&stack) == 2);
    assert(pop(&stack) == 1);

    clear_stack(&stack);
}

int main() {
    test_make_stack();
    return 0;
}