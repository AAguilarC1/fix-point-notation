#ifndef FIX_POINT_H
#define FIX_POINT_H 
#include <stdint.h>
#include <assert.h>

#define Q_FORMAT_6      6
#define Q_FORMAT_14     14
#define Q_FORMAT_30     30

#define Q_FORMAT_CUSTOM 16

#define Q_FORMAT Q_FORMAT_CUSTOM

#if !(Q_FORMAT > 0)
#error "Q_FORMAT must be greater than 0"
#endif

#if     Q_FORMAT == Q_FORMAT_6
typedef int8_t q7_t;
typedef int16_t q_long_t;
typedef q7_t q_t;
#elif   Q_FORMAT == Q_FORMAT_14
typedef int16_t q15_t;
typedef int32_t q_long_t;
typedef q15_t q_t;
#elif   Q_FORMAT == Q_FORMAT_30
typedef int32_t q31_t;
typedef int64_t q_long_t; 
typedef q31_t q_t;
#elif   Q_FORMAT == Q_FORMAT_CUSTOM
typedef int32_t q_t;
typedef int64_t q_long_t;
#else
#error "Q_FORMAT not supported"
#endif

#define FRACTIONAL_BITS (Q_FORMAT)
#define INT_BITS (Q_FORM_INT_BITS - FRACTIONAL_BITS)

#define Q_FORM_INT_BITS (sizeof(q_t) << 3)

#define Q_FORM_INT_MASK (((1 << INT_BITS) - 1) << FRACTIONAL_BITS)
#define Q_FORM_FRACTIONAL_MASK ((1 << FRACTIONAL_BITS) - 1)

#define GET_FORMAT (Q_FORMAT)

#define INT_TO_Q(__X__) ((q_t)((__X__) << FRACTIONAL_BITS))
#define Q_TO_INT(__Q__) ((int32_t)(__Q__) >> FRACTIONAL_BITS)


#define Q_MAX_INT    ((1 << (INT_BITS - 1))  - 1) // 2^(INT_BITS - 1) - 1 because of sign bit
#define Q_RESOLUTION (q_to_float(1))

#define Q_MINUS_ONE      INT_TO_Q(-1)
#define Q_MINUS_ONE_HALF (INT_TO_Q(-1) >> 1)
#define Q_ZERO           INT_TO_Q(0)
#define Q_ONE_HALF       (INT_TO_Q(1) >> 1)
#define Q_ONE            INT_TO_Q(1)
#define Q_TWO            INT_TO_Q(2)

#define Q_PI         float_to_q(3.14159265358979323846)
#define Q_TWO_PI     float_to_q(6.28318530717958647692)
#define Q_TAI        Q_TWO_PI      
#define Q_HALF_PI    float_to_q(1.57079632679489661923)
#define Q_QUARTER_PI float_to_q(0.78539816339744830962)
#define Q_THIRD_PI   float_to_q(1.04719755119659774615)
#define Q_SIXTH_PI   float_to_q(0.52359877559829887308)
#define Q_E          float_to_q(2.71828182845904523536)

#define Q_SIGN_BIT(__Q__)   (((__Q__) >> (Q_FORM_INT_BITS - 1)) & 1)
#define Q_SIGN(__Q__)       (Q_SIGN_BIT(__Q__) == Q_ONE ? 1 : -1)

q_t float_to_q(float x);
float q_to_float(q_t x);

q_t q_product(q_t a, q_t b);
q_t q_division(q_t a, q_t b);
q_t q_int_power(q_t a, int32_t n);
q_t q_absolute(q_t a);
q_t q_sqrt(q_t a);

#define Q_TRIGONOMETRIC_FUNCTIONS
#ifdef Q_TRIGONOMETRIC_FUNCTIONS

#define Q_TWO_FACTORIAL   Q_TWO
#define Q_THREE_FACTORIAL INT_TO_Q(6)
#define Q_FOUR_FACTORIAL  INT_TO_Q(24)
#define Q_FIVE_FACTORIAL  INT_TO_Q(120)
#define Q_SIX_FACTORIAL   INT_TO_Q(720)
#define Q_SEVEN_FACTORIAL INT_TO_Q(5040)

// Cosine Taylor series coefficients
#define Q_COS_K1        Q_ONE_HALF // First cosine Taylor coefficient => 1/2!

#if FRACTIONAL_BITS == Q_FORMAT_6 || FRACTIONAL_BITS >= 5
// Sine Taylor series coefficients
#define Q_SIN_K1        q_division(Q_ONE, Q_THREE_FACTORIAL) // First sine Taylor coefficient => 1/3!

// Cosine Taylor series coefficients
#define Q_COS_K2        q_division(Q_ONE, Q_FOUR_FACTORIAL) // Second cosine Taylor coefficient => 1/4!

#if FRACTIONAL_BITS == Q_FORMAT_14 || FRACTIONAL_BITS >= 13
// Sine Taylor series coefficients
#define Q_SIN_K2        q_division(Q_ONE, Q_FIVE_FACTORIAL)  // Second sine Taylor coefficient => 1/5!
#define Q_SIN_K3        q_division(Q_ONE, Q_SEVEN_FACTORIAL) // Third sine Taylor coefficient => 1/7! 

// Cosine Taylor series coefficients
#define Q_COS_K3        q_division(Q_ONE, Q_SIX_FACTORIAL)   // Third cosine Taylor coefficient => 1/6!  
#endif // FRACTIONAL_BITS > Q_FORMAT_14 || FRACTIONAL_BITS >= 13

#endif // FRACTIONAL_BITS > Q_FORMAT_6  || FRACTIONAL_BITS >= 5
//TODO: Add trigonometric functions

q_t q_sin(q_t a);
q_t q_cos(q_t a);

#endif // Q_TRIGONOMETRIC_FUNCTIONS



#endif // FIX_POINT_H
