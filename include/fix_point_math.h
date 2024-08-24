#ifndef FIX_POINT_MATH_H
#define FIX_POINT_MATH_H
#include "fix_point.h"

q_t q_product(q_t a, q_t b);
q_t q_division(q_t a, q_t b);
q_t q_int_power(q_t a, int32_t n);
q_t q_absolute(q_t a);
q_t q_sqrt(q_t a);

q_t q_sin(q_t a);
q_t q_cos(q_t a);
q_t q_tan(q_t a); 
// q_t q_cot(q_t a); // Deprecated
// q_t q_sec(q_t a); // Deprecated
// q_t q_csc(q_t a); // Deprecated

#endif // FIX_POINT_MATH_H
