#include <stdio.h>
#include "stack.h"
#include "push_swap.h"
#include "util.h"

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        debug("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }
    
    t_stack a;
    make_stack(&a, MAX_STACK_SIZE);
    t_stack b;
    make_stack(&b, MAX_STACK_SIZE);
    
    for (int i = argc - 1; i > 0; i--) {
        push(&a, atoi(argv[i]));
    }
    
    int pivot = median(&a);

    while (!is_empty(&a)) {
        int val = pop(&a);
        push(&b, val);
        output("pb\n");
        if (val < pivot) {
            rot(&b);
            output("rb\n");
        }
    }

    debug("a:\n");
    debug_stack(&a);
    debug("b:\n");
    debug_stack(&b);
    debug("----\n");

    while (!is_empty(&b)) {
        int min_cost = aligmnent_cost(&a, &b, 0, 0);
        int min_cost_offset = 0;
        for (int i = 1; i < size(&b); i++) {
            int cost = aligmnent_cost(&a, &b, i, 0);
            if (cost < min_cost) {
                min_cost = cost;
                min_cost_offset = i;
            }
        }
        aligmnent_cost(&a, &b, min_cost_offset, 1);
        push(&a, pop(&b));
        output("pa\n");


        debug("min_cost = %d\n", min_cost);
        debug("min_cost_offset = %d\n", min_cost_offset);
        debug("a:\n");
        debug_stack(&a);
        debug("b:\n");
        debug_stack(&b);
        debug("----\n");
    }

    debug("a:\n");
    debug_stack(&a);
    debug("b:\n");
    debug_stack(&b);
    debug("----\n");

    int min_val_offset = find_min_val_offset(&a);
    int rmin_val_offset = size(&a) - min_val_offset;

    if (min_val_offset < rmin_val_offset) {
        for (int i = 0; i < min_val_offset; i++) {
            rot(&a);
            output("ra\n");
        }
    } else {
        for (int i = 0; i < rmin_val_offset; i++) {
            rrot(&a);
            output("rra\n");
        }
    }
   
    debug("a:\n");
    debug_stack(&a);
    debug("b:\n");
    debug_stack(&b);
    debug("----\n");

    clear_stack(&a);
    clear_stack(&b);
    return 0;
}