I've spent a long time trying to make merge sort or quick sort fit into the task constraints 
and I'm rather disappointed with the lack of sophistication in the passing solution. 

Basically, we push everything onto stack B and greadily find the next value cheapest to push back into A.

Pivoting on median when pushing onto B slightly reduces the number of operations.

Finally, A is rotated to the correct position.

Slightly below 5000 ops to sort 500 numbers.

## Testing/Debugging

```
gcc main.c push_swap.c util.c stack.c -DDEBUG -o push_swap

gcc test.c stack.c -o test_push_swap

./push_swap 1 2 3 4 5 6 7 8 9 10 5
```

## Prod

```
gcc main.c push_swap.c util.c stack.c -DOUTPUT -o push_swap

ARG=$(shuf -i 1-500 | tr '\n' ' '); ./push_swap $ARG | ./checker_Mac $ARG

ARG=$(shuf -i 1-500 | tr '\n' ' '); ./push_swap $ARG | wc -l

for i in $(seq 1 100); do ARG=$(shuf -i 1-500 | tr '\n' ' '); ./push_swap $ARG | wc -l; done | sort | tail -n 1
# 4903
```