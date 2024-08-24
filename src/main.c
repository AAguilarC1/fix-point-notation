#include <stdio.h>
#define Q_FORMAT_CUSTOM 10
#include "../include/fix_point_math.h"

int main() {
    q_t x = float_to_q(-70);
    Q_PRINT(x);

    q_t y = float_to_q(0.01234);
    Q_PRINT(y);

    q_t z = float_to_q(1/2.0);
    Q_PRINT(z);

    q_t neg_pi = -Q_PI;
    Q_PRINT(neg_pi);

    float angle = (43.12394);
    q_t a = float_to_q(angle);
    q_t b = q_sin(a);

    printf("sin(%f) = %f\n",angle , q_to_float(b)); 

    PRINT_FORMAT;
    PRINT_MAX_INT;
    PRINT_MIN_INT;
    PRINT_RESOLUTION;
    PRINT_RANGE;

    return 0;
}
