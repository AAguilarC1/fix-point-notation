#include <stdio.h>
#include "../include/fix_point_math.h"

int main() {
    q_t x = INT_TO_Q(-70);
    Q_PRINT(x);

    q_t y = float_to_q(0.01234);
    Q_PRINT(y);

    q_t z = float_to_q(1/2.0);
    Q_PRINT(z);

    q_t neg_pi = -Q_PI;
    Q_PRINT(neg_pi);

    PRINT_FORMAT;
    PRINT_RANGE;
    PRINT_RESOLUTION;

    return 0;
}