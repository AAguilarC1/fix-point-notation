#include "../include/fix_point_math.h"

/**
 * @brief This functions multiplies two fixed point numbers (a*b)
 * 
 * @param a The first fixed point number
 * @param b The second fixed point number
 * @return q_t The result of the multiplication
 */
inline q_t q_product(q_t a, q_t b) {
    /*
        In order to perform the multiplication we need to upscale one of the fix point number in order to allow for the overflow
        that may occur during the multiplication. Then downscale the result to the original format.
    */
    return ((q_long_t) a * b) >> FRACTIONAL_BITS;
}

/**
 * @brief This function divides two fixed point numbers (a/b)
 * 
 * @param a The numerator of the division
 * @param b The denominator of the division
 * @return q_t The result of the division
 */
inline q_t q_division(q_t a, q_t b) {
    /*
        In order to perform the division we need to upscale the numerator in order to allow for the overflow that occurs when
        performing the fractional bit shift.
    */
    return (((q_long_t) (a) << FRACTIONAL_BITS) / b);
}

/**
 * @brief This function returns the absolute value of a fixed point number
 * 
 * @param a The fixed point number to get the absolute value of
 * @return q_t The absolute value of the fixed point number
 */
inline q_t q_absolute(q_t a){
    q_t mask = a >> (Q_FORM_INT_BITS - 1); // mask = 0xFFFFFFFF if a is negative, 0x00000000 otherwise
    // if a is negative, return -a, otherwise return a
    return (a ^ mask) - mask; 
}

/**
 * @brief This function raises a fixed point number to an integer power (a^n)
 * 
 * @param a The fixed point number to be raised to a power
 * @param n The power to raise the fixed point number to
 * @return q_t  The result of the fixed point number raised to the power
 */
q_t q_int_power(q_t a, int32_t n){
    if (n == 0) return Q_ONE; // a^0 = 1
    if (a == 0) return Q_ZERO; // 0^n = 0

    if (n < 0) {
        a = q_division(INT_TO_Q(1), a); // a^(-n) = 1/(a^n)
        n = -n;
    }

    return q_product(a, q_int_power(a, n - 1));
}

//TODO: Add q_float_power

/**
 * @brief The square root of a fixed point number using Newton's method (a^(1/2))
 * 
 * @param a The fixed point number to get the square root of
 * @return q_t The square root of the fixed point number
 */
q_t q_sqrt(q_t a){
    assert(a >= 0 && "The square root of a negative number is not a real number"); // The square root of a negative number is not a real number

    if (a == 0) return Q_ZERO; // sqrt(0) = 0

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

/**
 * @brief This function returns the sine of a fixed point number (sin(a))
 * 
 * @param a The angle in radians
 * @return q_t Returns the sine of the angle
 */
q_t q_sin(q_t a)
{
    // Pythagorean trigonometric identity Sin^2(a) + Cos^2(a) = 1 
    // Sin(a) = sqrt(1 - cos(a)^2)
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

/**
 * @brief This function returns the cosine of a fixed point number (cos(a))
 * 
 * @param a The angle in radians
 * @return q_t The cosine of the angle
 */
q_t q_cos(q_t a){
    // Bhaskara II's cosine approximation
    // cos(y) \approx = \frac{pi^{2} - 4y^{2}}}{pi^{2} + y^{2}} 
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

q_t q_tan(q_t a){
    if (q_cos(a) <= (2*Q_RESOLUTION) && q_cos(a) >= (-2*Q_RESOLUTION)){
        return INT_TO_Q(Q_MAX_INT); // Infinity is not possible in fixed point because of the limited range of the data type
    }
    return q_division(q_sin(a), q_cos(a));
}

// Deprecated while finding better approximation
/*
q_t q_sec(q_t a){
    q_t cosine = q_cos(a);
    if (cosine <= (Q_RESOLUTION) && cosine >= -(Q_RESOLUTION)){
        return INT_TO_Q(Q_MAX_INT); // Infinity is not possible in fixed point because of the limited range of the data type
    }
    return q_division(Q_ONE, cosine);
}

q_t q_csc(q_t a){
    q_t sine = q_sin(a);
    if (sine <= (Q_RESOLUTION) && sine >= -(Q_RESOLUTION)){
        return INT_TO_Q(Q_MAX_INT); // Infinity is not possible in fixed point because of the limited range of the data type
    }
    return q_division(Q_ONE, sine);
}

q_t q_cot(q_t a){
    q_t sine = q_sin(a);
    if (sine <= (Q_RESOLUTION) && sine >= -(Q_RESOLUTION)){
        return INT_TO_Q(Q_MAX_INT); // Infinity is not possible in fixed point because of the limited range of the data type
    }
    return q_division(q_cos(a), sine);
}
*/