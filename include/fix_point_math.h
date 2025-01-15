#ifndef FIX_POINT_MATH_H
#define FIX_POINT_MATH_H
#include <stdlib.h>
#include <stdio.h>
#include "fix_point.h"

q_t q_product(q_t a, q_t b);
q_t q_division(q_t a, q_t b);
q_t q_int_power(q_t a, int32_t n);
q_t q_absolute(q_t a);
q_t q_sqrt(q_t a);

q_t q_sin(q_t a);
q_t q_cos(q_t a);
q_t q_tan(q_t a); 

q_t q_rand(q_t min, q_t max);

#endif // FIX_POINT_MATH_H
