#include "../include/fix_point_math.h"

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
    if (n == 0) return Q_ONE;
    if (a == 0) return Q_ZERO;

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
    const q_t EPSILON = float_to_q(0.001);

    q_t Y = Q_ONE;
    uint8_t n = 10; // max Number of iterations
    // Newton's method for square root
    while((q_absolute(q_division(a, Y) - Y) > EPSILON) && (n > 0)){
        Y = q_division(q_division(a, Y) + Y, TWO);
        n--;
    }

    return Y;
}

q_t q_sin(q_t a)
{
    q_t ret = Q_ZERO;

    q_t x = a % Q_TWO_PI;
    q_t sign = Q_ONE;

    if (x > Q_PI) {
        x -= Q_TWO_PI;
    }

    if (x < Q_NEG_PI) {
        x += Q_TWO_PI;
    }

    // Adjust the sign based on the quadrant
    if (x > 0) {
        sign = Q_ONE;
    } 
    if (x < 0) {
        sign = Q_MINUS_ONE;
    }

    q_t _cos = q_cos(a);
    q_t cos2 = q_product(_cos, _cos);

    ret = Q_ONE - cos2;
    ret = q_sqrt(ret);

    ret = q_product(ret, sign);

    return ret;
}

// cos(y) \approx = \frac{pi^{2} - 4y^{2}}}{pi^{2} + y^{2}} 
q_t q_cos(q_t a){
    q_t ret = Q_ZERO;
    q_t sign = Q_ONE;

    q_t x = a % Q_TWO_PI;
    
    if (x > Q_PI) {
        x -= Q_TWO_PI;
    } 
    if (x < Q_NEG_PI) {
        x += Q_TWO_PI;
    }

    // Adjust the sign based on the quadrant
    if (x > Q_HALF_PI) {
        x = Q_PI - x;
        sign = Q_MINUS_ONE;
    } else if (x < Q_NEG_HALF_PI) {
        x = Q_NEG_PI - x;
        sign = Q_MINUS_ONE;
    }

    q_t pi2 = q_product(Q_PI, Q_PI);
    q_t x2 = q_product(x, x);
    q_t x2_4 = x2 + x2 + x2 + x2;

    q_t num = pi2 - x2_4;
    q_t den = pi2 + x2;

    ret = q_division(num, den);

    return q_product(ret, sign);
}

// TODO: Add tangent

