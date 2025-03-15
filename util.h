#ifndef UTIL_H
#define UTIL_H

int atoi(const char *str);
int min(int a, int b);
int max(int a, int b);
void insertion_sort(int *arr, int n);

# ifdef DEBUG
# define debug(...) printf(__VA_ARGS__)
# else
# define debug(...)
# endif

# ifdef OUTPUT
# define output(...) printf(__VA_ARGS__)
# else
# define output(...)
# endif

#endif // UTIL_H