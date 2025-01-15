#include "../include/fix_point_complex.h"

q_complex_t q_complex_alloc(q_t real, q_t imag)
{
    q_complex_t complex_val;
    complex_val.real = real;
    complex_val.imag = imag;
    return complex_val;
}

void q_complex_sum(q_complex_t* src, q_complex_t* dst)
{
    dst->real += src->real;
    dst->imag += src->imag;
}

void q_complex_mult(q_complex_t* src, q_complex_t* dst)
{
    q_t real = q_product(dst->real, src->real) - q_product(dst->imag, src->imag);
    q_t imag = q_product(dst->real, src->imag) + q_product(dst->imag, src->real);
    dst->real = real;
    dst->imag = imag;

}

void q_complex_div(q_complex_t* src, q_complex_t* dst);

void q_complex_free(q_complex_t* complex)
{
    complex->real = 0;
    complex->imag = 0;
}
