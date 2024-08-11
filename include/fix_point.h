#ifndef FIX_POINT_H
#define FIX_POINT_H 
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define Q_FORMAT_7      7
#define Q_FORMAT_15     15
#define Q_FORMAT_31     31

#define Q_FORMAT_CUSTOM 16

#define Q_FORMAT Q_FORMAT_CUSTOM

#if !(Q_FORMAT > 0)
#error "Q_FORMAT must be greater than 0"
#endif

#if     Q_FORMAT == Q_FORMAT_7
typedef int8_t q7_t;
typedef int16_t q_long_t;
typedef q7_t q_t;
#elif   Q_FORMAT == Q_FORMAT_15
typedef int16_t q15_t;
typedef int32_t q_long_t;
typedef q15_t q_t;
#elif   Q_FORMAT == Q_FORMAT_31
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
#define Q_MIN_INT    (-(1 << (INT_BITS - 1))) // -2^(INT_BITS - 1) because of sign bit
#define Q_RESOLUTION (q_to_float(1))

#define Q_MINUS_ONE      INT_TO_Q(-1)
#define Q_MINUS_ONE_HALF (float_to_q(-0.5f))
#define Q_ZERO           0
#define Q_ONE_HALF       (float_to_q(0.5f))
#define Q_ONE            INT_TO_Q(1)
#define Q_TWO            INT_TO_Q(2)

#define Q_PI         float_to_q(3.14159265358979323846f)
#define Q_TWO_PI     float_to_q(6.28318530717958647692f)
#define Q_TAI        Q_TWO_PI      
#define Q_HALF_PI    float_to_q(1.57079632679489661923f)
#define Q_QUARTER_PI float_to_q(0.78539816339744830962f)
#define Q_THIRD_PI   float_to_q(1.04719755119659774615f)
#define Q_SIXTH_PI   float_to_q(0.52359877559829887308f)
#define Q_E          float_to_q(2.71828182845904523536f)

#define Q_SIGN_BIT(__Q__)   (((__Q__) >> (Q_FORM_INT_BITS - 1)) & 1)
#define Q_SIGN(__Q__)       (Q_SIGN_BIT(__Q__) == Q_ONE ? 1 : -1)

#define Q_PRINT(__Q__) q_print((__Q__), (#__Q__))
#define PRINT_MAX_INT printf("Q_MAX_INT = %d\n", (Q_MAX_INT))
#define PRINT_MIN_INT printf("Q_MIN_INT = %d\n", (Q_MIN_INT))
#define PRINT_RANGE printf("Q_RANGE = [%d, %d]\n", (Q_MIN_INT), (Q_MAX_INT))
#define PRINT_RESOLUTION printf("Q_RESOLUTION = %e\n", Q_RESOLUTION)
#define PRINT_FORMAT printf("Q_FORMAT => Q%d.%d\n", INT_BITS-1, GET_FORMAT)

q_t float_to_q(float x);
float q_to_float(q_t x);
void q_print(q_t x, char* var_name);

#endif // FIX_POINT_H
