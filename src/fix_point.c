#include "../include/fix_point.h"

inline q_t float_to_q(float x) {
    return (q_t) (x * (1 << FRACTIONAL_BITS));
}

inline float q_to_float(q_t x) {
    return (float) x / (1 << FRACTIONAL_BITS);
}

q_t q_product(q_t a, q_t b) {
    return ((q_long_t) a * b) >> FRACTIONAL_BITS;
}

q_t q_division(q_t a, q_t b) {
    return (((q_long_t) (a) << FRACTIONAL_BITS) / b);
}

q_t q_absolute(q_t a){
    q_t mask = a >> (Q_FORM_INT_BITS - 1);
    return (a ^ mask) - mask;
}

q_t q_int_power(q_t a, int32_t n){
    if (a == 0) return INT_TO_Q(0);
    if (n == 0) return INT_TO_Q(1);

    if (n < 0) {
        a = q_division(INT_TO_Q(1), a);
        n = -n;
    }


    return q_product(a, q_int_power(a, n - 1));
}

