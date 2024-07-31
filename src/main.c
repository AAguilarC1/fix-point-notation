#include <stdio.h>
#include "../include/fix_point_math.h"

int main() {
    printf("Hello, World!\n");
    q_t x = INT_TO_Q(-70);
    Q_PRINT(x);

    q_t z = float_to_q(1/2.0);
    Q_PRINT(z);

    q_t y = float_to_q(0.01234);
    Q_PRINT(y);

    printf("GET_FORMAT = %d\n", GET_FORMAT);
    printf("Q_RESOLUTION = %e\n", Q_RESOLUTION);
    printf("Q_MAX_INT = %d\n", Q_MAX_INT);
    
    return 0;
}