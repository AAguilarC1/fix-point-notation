#include "../include/fix_point.h"

//TODO: add documentation to each function

inline q_t float_to_q(float x) {
    return (q_t) (x * (1 << FRACTIONAL_BITS));
}

inline float q_to_float(q_t x) {
    return (float) x / (1 << FRACTIONAL_BITS);
}

inline q_t q_product(q_t a, q_t b) {
    return ((q_long_t) a * b) >> FRACTIONAL_BITS;
}

inline q_t q_division(q_t a, q_t b) {
    return (((q_long_t) (a) << FRACTIONAL_BITS) / b);
}

inline q_t q_absolute(q_t a){
    q_t mask = a >> (Q_FORM_INT_BITS - 1);
    return (a ^ mask) - mask;
}

q_t q_int_power(q_t a, int32_t n){
    if (a == 0) return Q_ZERO;
    if (n == 0) return Q_ONE;

    if (n < 0) {
        a = q_division(INT_TO_Q(1), a);
        n = -n;
    }

    return q_product(a, q_int_power(a, n - 1));
}

//TODO: Add q_float_power

q_t q_sqrt(q_t a){
    assert(a >= 0 && "The square root of a negative number is not a real number");

    if (a == 0) return Q_ZERO;

    const q_t TWO     = INT_TO_Q(2);
    const q_t EPSILON = q_to_float(0.001);

    q_t Y = Q_ONE;
    uint8_t n = 10; // max Number of iterations
    // Newton's method for square root
    while((q_absolute(q_division(a, Y) - Y) > EPSILON) && (n > 0)){
        Y = q_division(q_division(a, Y) + Y, TWO);
        n--;
    }

    return Y;
}
