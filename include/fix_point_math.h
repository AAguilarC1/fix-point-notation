#ifndef FIX_POINT_MATH_H
#define FIX_POINT_MATH_H
#include "fix_point.h"

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

#endif // FIX_POINT_MATH_H
