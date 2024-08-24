#include "../include/fix_point.h"

//TODO: add documentation to each function

inline q_t float_to_q(float x) {
    return (q_t) (x * (1 << FRACTIONAL_BITS));
}

inline float q_to_float(q_t x) {
    return (float) x / (1 << FRACTIONAL_BITS);
}

void q_print(q_t value, char* var_name){
    printf("var %s: {\n", var_name);
    printf("\tq format: %d,\n", value);
    printf("\tfloat format: %f\n", q_to_float(value));
    printf("}\n");
}
