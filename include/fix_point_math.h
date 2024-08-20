#ifndef FIX_POINT_MATH_H
#define FIX_POINT_MATH_H
#include "fix_point.h"

q_t q_product(q_t a, q_t b);
q_t q_division(q_t a, q_t b);
q_t q_int_power(q_t a, int32_t n);
q_t q_absolute(q_t a);
q_t q_sqrt(q_t a);

#define q_sec(__a__) q_division(INT_TO_Q(1), q_cos(__a__))
#define q_csc(__a__) q_division(INT_TO_Q(1), q_sin(__a__))
#define q_cot(__a__) q_division(q_cos(__a__), q_sin(__a__))

q_t q_sin(q_t a);
q_t q_cos(q_t a);

//TODO: Use another method to calculate tan because the error is too high near the asymptotes
q_t q_tan(q_t a); // Not recommended to use the error is too high near the asymptotes

#endif // FIX_POINT_MATH_H
