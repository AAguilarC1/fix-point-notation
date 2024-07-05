#ifndef FIX_POINT_H
#define FIX_POINT_H 
#include <stdint.h>

#define Q_FORMAT_7      7
#define Q_FORMAT_15     15
#define Q_FORMAT_31     31

#define Q_FORMAT_CUSTOM 16

#define Q_FORMAT Q_FORMAT_CUSTOM

#if     Q_FORMAT == Q_FORMAT_7
typedef int8_t q7_t;
typedef q7_t q_t;
#elif   Q_FORMAT == Q_FORMAT_15
typedef int16_t q15_t;
typedef q15_t q_t;
#elif   Q_FORMAT == Q_FORMAT_31
typedef int32_t q31_t;
typedef q31_t q_t;
#elif   Q_FORMAT == Q_FORMAT_CUSTOM
typedef int32_t q_t;
#else
#error "Q_FORMAT not supported"
#endif

#define FRACTIONAL_BITS (Q_FORMAT)
#define GET_FORMAT (FRACTIONAL_BITS)

#define INT_TO_Q(x) ((q_t)((x) << FRACTIONAL_BITS))
#define Q_TO_INT(x) ((int32_t)(x) >> FRACTIONAL_BITS)

#endif // FIX_POINT_H