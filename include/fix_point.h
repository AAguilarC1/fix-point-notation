#ifndef FIX_POINT_H
#define FIX_POINT_H 
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

// Sign bit is the most significant bit
// Therefor the maximum number of bits that can be used is 31

// Fix point notation is define as Qm.n
// Where m is the number of bits used for the integer part
// and n is the number of bits used for the fractional part
// Fix point notation is used to represent real numbers in binary form by using fixed number of bits for the integer and fractional part respectively.
// The range of the number is [-2^(m-1), 2^(m-1) - 2^(-n)]
// The resolution of the number is 2^(-n)

// Example of Q3.4:
// - 3 bits for the integer part
// - 4 bits for the fractional part
// Max integer value = 2^(3-1) - 1 = 3
// Max fractional value = 2^-4 = 0.0625
// Range = [-4, 3.9375]
// 2.5 = 0010 1000 = 0x28 (or 40 in base 10)
// In this example we must imagine there is radix point between the 4th and 5th bit (With a sign bit at the most significant bit)
// Representation => 0010 . 1000 = 2.5. Which comes from:
//  (0 * 2^3) (0 * 2^2) (1 * 2^1) (0 * 2^0) . (1 * 2^-1) (0 * 2^-2) (0 * 2^-3) (0 * 2^-4)  
// 2 * 2^0 + 1 * 2^-1 = 2 + 0.5 = 2.5
// Therefore, 0010 = 2 and 1000 = 0.5.

#define Q_FORMAT_7      7  // Q0.7 => Where max bits = 8
#define Q_FORMAT_15     15 // Q0.15 => Where max bits = 16
#define Q_FORMAT_31     31 // Q0.31 => Where max bits = 32

#ifndef Q_FORMAT_CUSTOM
#define Q_FORMAT_CUSTOM 16
#endif // Q_FORMAT_CUSTOM

#ifndef Q_FORMAT
#define Q_FORMAT Q_FORMAT_CUSTOM
#endif // Q_FORMAT

#if !(Q_FORMAT > 0)
#error "Q_FORMAT must be greater than 0"
#endif

// Check which of the following Q_FORMAT is defined
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

#define FRACTIONAL_BITS (Q_FORMAT) // Number of bits used for the fractional part
#define Q_FORM_INT_BITS (sizeof(q_t) << 3) // Total number of bits in the q_t type
#define INT_BITS (Q_FORM_INT_BITS - FRACTIONAL_BITS) // Number of bits used for the integer part

#define Q_FORM_INT_MASK (((1 << INT_BITS) - 1) << FRACTIONAL_BITS) // Mask for the integer part
#define Q_FORM_FRACTIONAL_MASK ((1 << FRACTIONAL_BITS) - 1) // Mask for the fractional part

#define GET_FORMAT (Q_FORMAT) // Get the format of the Qm.n

#define INT_TO_Q(__X__) ((q_t)((__X__) << FRACTIONAL_BITS))     // Convert integer to Qm.n
#define Q_TO_INT(__Q__) ((int32_t)(__Q__) >> FRACTIONAL_BITS)   // Convert Qm.n to integer

#define Q_MAX_INT    ((1 << (INT_BITS - 1)))                 // 2^(INT_BITS - 1) - 1 because of sign bit
#define Q_MIN_INT    (-(1 << (INT_BITS - 1)))                     // -2^(INT_BITS - 1) because of sign bit
#define Q_MAX_FLOAT  (q_to_float((1 << Q_FORM_INT_BITS - 1) - 1)) // Maximum float value
#define Q_MIN_FLOAT  (q_to_float((1 << Q_FORM_INT_BITS - 1)))     // Minimum float value
#define Q_RESOLUTION (q_to_float(1))

#define Q_MINUS_ONE      INT_TO_Q(-1) // Qm.n representation of -1
#define Q_MINUS_ONE_HALF (float_to_q(-0.5f)) // Qm.n representation of -0.5
#define Q_ZERO           0 // Qm.n representation of 0
#define Q_ONE_HALF       (float_to_q(0.5f)) // Qm.n representation of 0.5
#define Q_ONE            INT_TO_Q(1) // Qm.n representation of 1
#define Q_TWO            INT_TO_Q(2) // Qm.n representation of 2

#define Q_NEG_HALF_PI   float_to_q(-1.57079632679489661923f) // Qm.n representation of -pi/2
#define Q_NEG_PI        float_to_q(-3.14159265358979323846f) // Qm.n representation of -pi
#define Q_PI            float_to_q(3.14159265358979323846f)  // Qm.n representation of pi
#define Q_TWO_PI        float_to_q(6.28318530717958647692f)  // Qm.n representation of 2pi
#define Q_TAU           Q_TWO_PI // Qm.n representation of tau
#define Q_HALF_PI       float_to_q(1.57079632679489661923f) // Qm.n representation of pi/2
#define Q_QUARTER_PI    float_to_q(0.78539816339744830962f) // Qm.n representation of pi/4
#define Q_THIRD_PI      float_to_q(1.04719755119659774615f) // Qm.n representation of pi/3
#define Q_SIXTH_PI      float_to_q(0.52359877559829887308f) // Qm.n representation of pi/6
#define Q_E             float_to_q(2.71828182845904523536f) // Qm.n representation of Euler's number

#define Q_SIGN_BIT(__Q__)   (((__Q__) >> (Q_FORM_INT_BITS - 1)) & 1) // Get the sign bit of the Qm.n number
#define Q_SIGN(__Q__)       (Q_SIGN_BIT(__Q__) == Q_ONE ? Q_ONE : Q_MINUS_ONE) // Get the sign of the Qm.n number

#define Q_PRINT(__Q__)    q_print((__Q__), (#__Q__)) // Print the Qm.n number
#define PRINT_MAX_INT     printf("Q_MAX_INT = %d\n", (Q_MAX_INT)) // Print the maximum integer value
#define PRINT_MIN_INT     printf("Q_MIN_INT = %d\n", (Q_MIN_INT)) // Print the minimum integer value
#define PRINT_RESOLUTION  printf("Q_RESOLUTION = %e\n", Q_RESOLUTION) // Print the resolution of the Qm.n number
#define PRINT_FORMAT      printf("Q_FORMAT => Q%d.%d\n", INT_BITS-1, GET_FORMAT) // Print the format of the Qm.n number
#define PRINT_RANGE       printf("Q_RANGE = [%d, %d)\n", (Q_MIN_INT), (Q_MAX_INT)) // Print the range of the Qm.n number
#define PRINT_MAX_FLOAT   printf("Q_MAX_FLOAT = %f\n", q_to_float(Q_MAX_FLOAT)) // Print the maximum float value
#define PRINT_MIN_FLOAT   printf("Q_MIN_FLOAT = %f\n", q_to_float(Q_MIN_FLOAT)) // Print the minimum float value

q_t float_to_q(float x);
float q_to_float(q_t x);
void q_print(q_t x, char* var_name);

#endif // FIX_POINT_H
