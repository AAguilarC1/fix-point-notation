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

#ifdef Q_TRIGONOMETRIC_FUNCTIONS

//TODO: Add trigonometric functions
q_t q_sin(q_t a)
{
    q_t sign = Q_ONE;
    q_t ret = Q_ZERO;
    q_t x = ( a ) % (Q_PI); 

    q_t k1  = Q_ZERO;
    q_t k2  = Q_ZERO;
    q_t k3  = Q_ZERO;

    {
        const q_t x2 = q_int_power(x, 2);

        const q_t x3 = q_product(x2, x);
        k1 = q_product(x3, Q_SIN_K1);

        #ifdef Q_SIN_K2 
        const q_t x5 = q_product(x2, x3);
        k2 = q_product(x5, Q_SIN_K2);
        #endif 

        #ifdef Q_SIN_K3
        const q_t x7 = q_product(x2, x5);
        k3 = q_product(x7, Q_SIN_K3);
        #endif
    
    }

    ret = x - k1 + k2 - k3;

    return ret;
}


q_t q_cos(q_t a){
    q_t ret = Q_ZERO;
    q_t sign = Q_ONE;

    q_t x = ( a ) % (Q_TWO_PI);

    if (x > Q_PI) {
        x -= Q_PI;
        sign = Q_MINUS_ONE;
    }

    q_t k1  = Q_ZERO;
    q_t k2  = Q_ZERO;
    q_t k3  = Q_ZERO;

    {
        const q_t x2 = q_int_power(x, 2);
        k1 = q_product(x2, Q_COS_K1);

        #ifdef Q_COS_K2
        const q_t x4 = q_int_power(x2, 2);
        k2 = q_product(x4, Q_COS_K2);
        #endif  // Q_COS_K2

        #ifdef Q_COS_K3
        const q_t x6 = q_product(x2, x4);
        k3 = q_product(x6, Q_COS_K3);
        #endif // Q_COS_K3
    }

    ret = q_product(Q_ONE - k1 + k2 - k3, sign);

    return ret;
}

#endif // Q_TRIGONOMETRIC_FUNCTIONS

