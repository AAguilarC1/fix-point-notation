#include <stdio.h>
#include "../include/fix_point.h"
int main() {
    printf("Hello, World!\n");
    q_t x = INT_TO_Q(-70);
    printf("x = %d\n", x);

    int32_t y = Q_TO_INT(x);
    printf("y = %d\n", y);

    q_t z = float_to_q(28.4738);
    printf("z = %d\n", z);

    float w = q_to_float(z);
    printf("w = %f\n", w);

    printf("GET_FORMAT = %d\n", GET_FORMAT);
    printf("Q_RESOLUTION = %e\n", Q_RESOLUTION);
    printf("Q_MAX_INT = %d\n", Q_MAX_INT);
    
    return 0;
}