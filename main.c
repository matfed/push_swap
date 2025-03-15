#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

void load_greater_part_of_top_b_segment_to_a(
    t_stack *a, t_stack *b, t_stack *a_segments, t_stack *b_segments) {
    int pivot = seek(b);
    debug("pivot = %d\n", pivot);
        
    int iters = pop(b_segments);

    if (iters == -1) {
        rrot(b);
        iters = 1;
    }

    if (iters == 1) {
        push(a, pop(b));
        push(a_segments, 1);
        return;
    }
    int backwards = 0;
    if (iters < 0) {
        iters = -iters;
        backwards = 1;
    }
    int new_segment_a = 0;
    int new_segment_b = 0;
    for (int i = 0; i < iters; i++) {
        if (backwards) {
            rrot(b);
        }
        if (seek(b) >= pivot) {
            push(a, pop(b));
            new_segment_a++;
        } else {
            if (!backwards)
                rot(b);
            new_segment_b++;
        }
    }
    if (new_segment_a > 0)
        push(a_segments, new_segment_a);
    if (new_segment_b > 0) {
        if (!backwards)
            new_segment_b = -new_segment_b;
        push(b_segments, new_segment_b);
    }
}

void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int find_pivot(t_stack *a, int iters, int backwards) {
    int tmp[MAX_SIZE];
    for (int i = 0; i < iters; i++) {
        int offset = i;
        if (backwards) {
            offset = -offset -1;
        }
        tmp[i] = seek_offset(a, i);
    }
    insertion_sort(tmp, iters);
    int pivot = tmp[iters / 2];
    return pivot;
}

void load_lesser_parts_of_top_a_segment_to_b(
    t_stack *a, t_stack *b, t_stack *a_segments, t_stack *b_segments) {
    while(1) {
        int iters = pop(a_segments);
        if (iters == -1) {
            rrot(a);
            iters = 1;
        }
        if (iters == 1) {
            push(a_segments, iters);
            break;
        }
        int backwards = 0;
        if (iters < 0) {
            iters = -iters;
            if (!is_empty(a_segments)) {
                backwards = 1;
            }
        }
        int pivot = find_pivot(a, iters, backwards);
        
        debug("pivot = %d\n", pivot);
        
        int new_segment_a = 0;
        int new_segment_b = 0;
        for (int i = 0; i < iters; i++) {
            if (backwards) {
                rrot(a);
            }
            if (seek(a) < pivot) {
                push(b, pop(a));
                new_segment_b++;
            } else {
                if (!backwards)
                    rot(a);
                new_segment_a++;
            }
        }
        if (new_segment_a > 0) {
            if (!backwards)
                push(a_segments, -new_segment_a);
            else 
                push(a_segments, new_segment_a);
        }
        if (new_segment_b > 0)
            push(b_segments, new_segment_b);
        if (new_segment_a == 0) 
            break;
        int new_pivot;
        for (int i = 0; i < new_segment_a; i++) {
            new_pivot = seek_offset(a, i);
            if (new_pivot != pivot) {
                break;
            }
        }
        if (new_pivot != pivot) {
            pivot = new_pivot;
        } else {
            break;
        }
    }  
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        debug("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }
    
    t_stack a;
    make_stack(&a, MAX_SIZE);
    t_stack b;
    make_stack(&b, MAX_SIZE);
    
    t_stack a_segments;
    make_stack(&a_segments, MAX_SIZE);
    t_stack b_segments;
    make_stack(&b_segments, MAX_SIZE);

    for (int i = 1; i < argc; i++) {
        push(&a, atoi(argv[i]));
    }
    push(&a_segments, argc - 1);

    debug("a:\n");
    debug_stack(&a);
    debug("b:\n");
    debug_stack(&b);
    debug("a_segments:\n");
    debug_stack(&a_segments);
    debug("b_segments:\n");
    debug_stack(&b_segments);
    debug("----\n");

    while (1) {
        debug("load_lesser_parts_of_top_a_segment_to_b\n");
        load_lesser_parts_of_top_a_segment_to_b(&a, &b, &a_segments, &b_segments);
        
        debug("a:\n");
        debug_stack(&a);
        debug("b:\n");
        debug_stack(&b);
        debug("a_segments:\n");
        debug_stack(&a_segments);
        debug("b_segments:\n");
        debug_stack(&b_segments);
        debug("----\n");
        if (is_empty(&b_segments)) {
            break;
        }

        debug("load_greater_part_of_top_b_segment_to_a\n");
        load_greater_part_of_top_b_segment_to_a(&a, &b, &a_segments, &b_segments);

        debug("a:\n");
        debug_stack(&a);
        debug("b:\n");
        debug_stack(&b);
        debug("a_segments:\n");
        debug_stack(&a_segments);
        debug("b_segments:\n");
        debug_stack(&b_segments);
        debug("----\n");
    }
    
    clear_stack(&a);
    clear_stack(&b);
    clear_stack(&a_segments);
    clear_stack(&b_segments);
    return 0;
}