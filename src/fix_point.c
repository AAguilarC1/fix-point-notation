#include "../include/fix_point.h"

inline q_t float_to_q(float x) {
    return (q_t)(x * (1 << FRACTIONAL_BITS));
}

inline float q_to_float(q_t x) {
    return (float)x / (1 << FRACTIONAL_BITS);
}
