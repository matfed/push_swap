#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

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

void load_greater_part_of_top_b_segment_to_a(
    t_stack *a, t_stack *b, t_stack *a_segments, t_stack *b_segments) {
    int iters = pop(b_segments);

    if (iters < 0 && iters >= -3) {
        iters = -iters;
        for (int i = 0; i < iters; i++) {
            rrot(b);
            output("rrb\n");
        }
    }

    if (iters >= 0 && iters <= 3) {
        for (int i = 0; i < iters; i++) {
            push(a, pop(b));
            output("pa\n");
        }
        push(a_segments, iters);
        return;
    }

    int backwards = 0;
    if (iters < 0) {
        iters = -iters;
        if (!is_empty(b_segments)) {
            backwards = 1;
        }
    }

    int pivot = find_pivot(b, iters, backwards);
    debug("pivot = %d\n", pivot);

    int new_segment_a = 0;
    int new_segment_b = 0;
    for (int i = 0; i < iters; i++) {
        if (backwards) {
            rrot(b);
            output("rrb\n");
        }
        if (seek(b) >= pivot) {
            push(a, pop(b));
            output("pa\n");
            new_segment_a++;
        } else {
            if (!backwards) {
                output("rb\n");
                rot(b);
            }
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

void load_lesser_parts_of_top_a_segment_to_b(
    t_stack *a, t_stack *b, t_stack *a_segments, t_stack *b_segments) {
    while(1) {
        int iters = pop(a_segments);

        if (iters < 0 && iters >= -3) {
            iters = -iters;
            for (int i = 0; i < iters; i++) {
                rrot(a);
                output("rra\n");
            }
        }

        if (iters == 1) {
            push(a_segments, iters);
            break;
        }
        if (iters == 2) {
            if (seek_offset(a, 0) > seek_offset(a, 1)) {
                swap(a);
                output("sa\n");
            }
            push(a_segments, iters);
            break;
        }
        if (iters == 3) {
            if (seek_offset(a, 1) < seek_offset(a, 0)) {
                swap(a);
                output("sa\n");
            }
            if (seek_offset(a, 2) < seek_offset(a, 1)) {
                rot(a);
                output("ra\n");
                swap(a);
                output("sa\n");
                rrot(a);
                output("rra\n");
            }
            if (seek_offset(a, 1) < seek_offset(a, 0)) {
                swap(a);
                output("sa\n");
            }

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
                output("rra\n");
            }
            if (seek(a) < pivot) {
                push(b, pop(a));
                output("pb\n");
                new_segment_b++;
            } else {
                if (!backwards) {
                    rot(a);
                    output("ra\n");
                }
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
    }  
}

int main2(int argc, char *argv[]) {
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

    for (int i = argc - 1; i > 0; i--) {
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

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
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

int calculate_aligmnent_cost(t_stack *a, t_stack *b, int offset, int execute) {
    int v = seek_offset(b, offset);
    int remove_cost = offset;
    int rremove_cost = size(b) - offset;
    
    int min_val_offset = find_min_val_offset(a);
    int a_offset = 0;
    int i;
    for (i = 0; i < size(a); i++) {
        a_offset = (i + min_val_offset) % size(a);
        if (seek_offset(a, a_offset) > v) {
            break;
        }
    }
    a_offset = (i + min_val_offset) % size(a);
    // if (size(a) == 0) {
    //     pos = 0;
    // }

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
        return mixed_cost;
    } else if (r_cost < rr_cost) {
        if (execute) {
            for (int i = 0; i < min(insert_cost, remove_cost); i++) {
                rot(a);
                rot(b);
                output("rr\n");
            }
            for (int i = 0; i < max(0, remove_cost - insert_cost); i++) {
                rot(b);
                output("rb\n");
            }
            for (int i = 0; i < max(0,  insert_cost - remove_cost); i++) {
                rot(a);
                output("ra\n");
            }
        }
        return r_cost;
    } else {
        if (execute) {
            for (int i = 0; i < min(rinsert_cost, rremove_cost); i++) {
                rrot(a);
                rrot(b);
                output("rrr\n");
            }
            for (int i = 0; i < max(0, rremove_cost - rinsert_cost); i++) {
                rrot(b);
                output("rrb\n");
            }
            for (int i = 0; i < max(0,  rinsert_cost - rremove_cost); i++) {
                rrot(a);
                output("rra\n");
            }
        }
        return rr_cost;
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
    
    for (int i = argc - 1; i > 0; i--) {
        push(&a, atoi(argv[i]));
    }
    
    while (!is_empty(&a)) {
        push(&b, pop(&a));
        output("pb\n");
    }

    debug("a:\n");
    debug_stack(&a);
    debug("b:\n");
    debug_stack(&b);
    debug("----\n");

    while (!is_empty(&b)) {
        int min_cost = calculate_aligmnent_cost(&a, &b, 0, 0);
        int min_cost_offset = 0;
        for (int i = 1; i < size(&b); i++) {
            int cost = calculate_aligmnent_cost(&a, &b, i, 0);
            if (cost < min_cost) {
                min_cost = cost;
                min_cost_offset = i;
            }
        }
        calculate_aligmnent_cost(&a, &b, min_cost_offset, 1);
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