#include "../include/fix_point_complex.h"

q_complex_t q_complex_alloc(q_t real, q_t imag)
{
    q_complex_t complex_val;
    complex_val.real = real;
    complex_val.imag = imag;
    return complex_val;
}

void q_complex_free(q_complex_t* complex)
{
    complex->real = 0;
    complex->imag = 0;
}
