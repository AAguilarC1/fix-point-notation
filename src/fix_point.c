#include "../include/fix_point.h"

/**
 * @brief This function converts a floating number to a fixed point number
 * 
 * @param x The floating number to be converted
 * @return q_t The fixed point number representation of the floating number
 */
inline q_t float_to_q(float x) {
    return (q_t) (x * (1 << FRACTIONAL_BITS));
}

/**
 * @brief This function converts a fixed point number to a floating number
 * 
 * @param x The fixed point number to be converted
 * @return float The floating number representation of the fixed point number
 */
inline float q_to_float(q_t x) {
    return ((float) x) / (1 << FRACTIONAL_BITS);
}

/**
 * @brief This functions prints the value of a fixed point number as well as its floating point representation
 * 
 * @param value The fixed point number to be printed
 * @param var_name The name of the variable to be printed
 */
void q_print(q_t value, char* var_name){
    printf("var %s: {\n", var_name);
    printf("\tq format: %d,\n", value);
    printf("\tfloat format: %f\n", q_to_float(value));
    printf("}\n");
}