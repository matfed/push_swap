#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"
#include "util.h"

int median(t_stack *a) {
    int tmp[MAX_STACK_SIZE];
    int stack_size = size(a);
    for (int i = 0; i < stack_size; i++) {
        tmp[i] = seek_offset(a, i);
    }
    insertion_sort(tmp, stack_size);
    int pivot = tmp[stack_size / 2];
    return pivot;
}

int find_min_val_offset(t_stack *st) {
    int min_val = seek(st);
    int min_val_offset = 0;
    for (int i = 0; i < size(st); i++) {
        int val = seek_offset(st, i);
        if (val < min_val) {
            min_val = val;
            min_val_offset = i;
        }
    }
    return min_val_offset;
}

int find_offset_for_value(t_stack *st, int value) {
    int min_val_offset = find_min_val_offset(st);
    int offset = 0;
    int i;
    for (i = 0; i < size(st); i++) {
        offset = (i + min_val_offset) % size(st);
        if (seek_offset(st, offset) > value) {
            break;
        }
    }
    offset = (i + min_val_offset) % size(st);
    return offset;
}

void execute_mixed_alignment(
    t_stack *a, t_stack *b,
    int insert_cost, int rinsert_cost,
    int remove_cost, int rremove_cost
) {
    if (insert_cost < rinsert_cost) {
        for (int i = 0; i < insert_cost; i++) {
            rot(a);
            output("ra\n");
        }
    } else {
        for (int i = 0; i < rinsert_cost; i++) {
            rrot(a);
            output("rra\n");
        }
    }
    if (remove_cost < rremove_cost) {
        for (int i = 0; i < remove_cost; i++) {
            rot(b);
            output("rb\n");
        }
    } else {
        for (int i = 0; i < rremove_cost; i++) {
            rrot(b);
            output("rrb\n");
        }
    }
}

void execute_alignment(
    t_stack *a, t_stack *b,
    int insert_cost, int remove_cost,
    int reverse
) {
    for (int i = 0; i < min(insert_cost, remove_cost); i++) {
        if (!reverse) { 
            rot(a);
            rot(b);
            output("rr\n");
        } else {
            rrot(a);
            rrot(b);
            output("rrr\n");
        }
    }
    for (int i = 0; i < max(0, remove_cost - insert_cost); i++) {
        if (!reverse) {
            rot(b);
            output("rb\n");
        } else {
            rrot(b);
            output("rrb\n");
        }
    }
    for (int i = 0; i < max(0,  insert_cost - remove_cost); i++) {
        if (!reverse) {
            rot(a);
            output("ra\n");
        } else {
            rrot(a);
            output("rra\n");
        }
    }
}

int aligmnent_cost(t_stack *a, t_stack *b, int offset, int execute) {
    int v = seek_offset(b, offset);
    int remove_cost = offset;
    int rremove_cost = size(b) - offset;
    
    int a_offset = find_offset_for_value(a, v);

    int insert_cost = a_offset;
    int rinsert_cost = size(a) - a_offset;
    debug("offset = %d\n", offset);
    debug("remove_cost = %d\n", remove_cost);
    debug("rremove_cost = %d\n", rremove_cost);
    debug("a_offset = %d\n", a_offset);
    debug("insert_cost = %d\n", insert_cost);
    debug("rinsert_cost = %d\n", rinsert_cost);
    debug("----\n");
    int r_cost = max(insert_cost, remove_cost);
    int rr_cost = max(rinsert_cost, rremove_cost);
    int mixed_cost = min(insert_cost, rinsert_cost) + min(remove_cost, rremove_cost);
    if (mixed_cost < r_cost && mixed_cost < rr_cost) {
        if (execute) {
            execute_mixed_alignment(a, b, insert_cost, rinsert_cost, remove_cost, rremove_cost);
        }
        return mixed_cost;
    } else if (r_cost < rr_cost) {
        if (execute) {
            execute_alignment(a, b, insert_cost, remove_cost, 0);
        }
        return r_cost;
    } else {
        if (execute) {
            execute_alignment(a, b, rinsert_cost, rremove_cost, 1);
        }
        return rr_cost;
    }
}