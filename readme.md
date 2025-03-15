
```
gcc main.c push_swap.c -DDEBUG -o push_swap


./push_swap 1 2 3 4 5 6 7 8 9 10 5


ARG=$(shuf -i 1-100 | tr '\n' ' '); ./push_swap $ARG | wc -l


ARG=$(shuf -i 1-5 | tr '\n' ' '); ./push_swap $ARG | ./checker_Mac $ARG
```