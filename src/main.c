#include <stdio.h>
#include "../include/fix_point.h"
int main() {
    printf("Hello, World!\n");
    q_t x = INT_TO_Q(70);
    printf("x = %d\n", x);

    int32_t y = Q_TO_INT(x);
    printf("y = %d\n", y);

    printf("GET_FORMAT = %d\n", GET_FORMAT);
    return 0;
}