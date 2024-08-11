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

    q_t a = Q_HALF_PI;
    q_t b = q_sin(a);
    q_t c = q_cos(a);

    printf("sin(3.291 * PI) = %f\n", q_to_float(b)); // Bug -> sin(3.291 * pi) = 0.7920 when it should be negative

    return 0;
}