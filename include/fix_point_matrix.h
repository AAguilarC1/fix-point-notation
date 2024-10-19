#ifndef FIX_POINT_MATRIX_H
#define FIX_POINT_MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#define Q_FORMAT_CUSTOM 16
#define Q_FORMAT Q_FORMAT_CUSTOM

#include "fix_point_math.h"

#define Q_EPSILON ((q_t) 1) // The smallest representable number in the fixed point format

#define Q_MATRIX_ASSERT(m) {\
    assert(((m) != NULL) && "Matrix is NULL");\
    assert(((m)->elements != NULL) && "Matrix elements are NULL");\
}

#define Q_MATRIX_AT(m, i, j) ((m)->elements[(i) * (m)->stride + (j)]) // Access the element at the i-th row and j-th column of the matrix
#define Q_MATRIX_PRINT(m) q_matrix_print(&(m), (#m)) // Print the matrix

#define q_matrix_square_alloc(size) q_matrix_alloc((size), (size)) // Allocate a square matrix

#define q_matrix_fill_float(m, value) q_matrix_fill((m), float_to_q((value))) // Fill the matrix with a given value in float format
#define q_ones(m)                     q_matrix_fill((m), Q_ONE) // Fill the matrix with ones
#define q_zeros(m)                    q_matrix_fill((m), Q_ZERO) // Fill the matrix with zeros
#define q_matrix_fill_rand_float(m, min, max) q_matrix_fill_rand((m), float_to_q((min)), float_to_q((max))) // Fill the matrix with random values in float format

#define q_matrix_scalar_mul_float(m, scalar) q_matrix_scalar_mul((m), float_to_q((scalar))) // Multiply the matrix by a scalar value in float format

#define q_matrix_is_approx_float(a, b, abs_tol) q_matrix_is_approx((a), (b), float_to_q((abs_tol))) // Check if the matrices are approximately equal within an absolute tolerance in float format
struct matrix_t {
    size_t rows;
    size_t cols;
    size_t stride;
    q_t* elements;
};
typedef struct matrix_t q_matrix_t;

enum status_t {
    Q_MATRIX_OK = 0,
    Q_MATRIX_ERROR = 1
};
typedef enum status_t q_status_t;

q_matrix_t q_matrix_alloc(size_t rows, size_t cols);

void q_matrix_slice_row(const q_matrix_t* m, q_matrix_t* dst, size_t row);
void q_matrix_slice_col(const q_matrix_t* m, q_matrix_t* dst, size_t col);
void q_matrix_submatrix(const q_matrix_t* m, q_matrix_t* dst, size_t row, size_t col);
void q_matrix_transpose(const q_matrix_t* m, q_matrix_t* dst);

void q_matrix_switch_rows(const q_matrix_t* m, q_matrix_t* dst, size_t row1, size_t row2);
void q_matrix_switch_cols(const q_matrix_t* m, q_matrix_t* dst, size_t col1, size_t col2);

void q_matrix_fill(const q_matrix_t* m, q_t value);
void q_matrix_identity(const q_matrix_t* m);
void q_matrix_fill_rand(const q_matrix_t* m, q_t min, q_t max);

// Linear algebra operations

void q_matrix_LU_decomposition(const q_matrix_t* m, q_matrix_t* L, q_matrix_t* U);
void q_matrix_PLU_decomposition(const q_matrix_t* m , q_matrix_t* P, q_matrix_t* L, q_matrix_t* U);
void q_matrix_forward_substitution(const q_matrix_t* L, const q_matrix_t* b, const q_matrix_t* Y);
void q_matrix_back_substitution(const q_matrix_t* U, const q_matrix_t* Y, const q_matrix_t* X);
void q_matrix_LU_solve(const q_matrix_t* L, const q_matrix_t* U, const q_matrix_t* b, const q_matrix_t* X);
void q_matrix_LUP_solve(const q_matrix_t* L, const q_matrix_t* U, const q_matrix_t* P, const q_matrix_t* b, const q_matrix_t* X);
void q_matrix_inverse(const q_matrix_t* m, q_matrix_t* dst); 

// Basic matrix operations

void q_matrix_sum(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst);
void q_matrix_scalar_mul(const q_matrix_t* m, q_t scalar);
void q_matrix_elementwise_mul(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst);

// Matrix operations 

q_t q_matrix_determinant(const q_matrix_t* m);
q_t q_matrix_trace(const q_matrix_t* m);
q_t q_matrix_sum_contents(const q_matrix_t* m);
q_t q_matrix_1_norm(const q_matrix_t* m);
q_t q_matrix_infinity_norm(const q_matrix_t* m);
q_t q_matrix_euclidean_norm(const q_matrix_t* m);

// Matrix operations

void q_cross_product(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst);
void q_matrix_dot_product(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst);
void q_matrix_eigenvalues(const q_matrix_t* m, q_matrix_t* dst); // TODO: might need to change the return type (Add complex numbers)
void q_matrix_eigenvectors(const q_matrix_t* m, q_matrix_t* dst); // TODO: might need to change the return type (Add complex numbers)

// Matrix validation

q_status_t q_matrix_is_equal(const q_matrix_t* a, const q_matrix_t* b); 
q_status_t q_matrix_is_approx(const q_matrix_t* a, const q_matrix_t* b, q_t abs_tol);

// Matrix memory management

void q_matrix_cpy(const q_matrix_t* src, q_matrix_t* dst);
void q_matrix_free(q_matrix_t* m);
void q_matrix_freeDeep(q_matrix_t* m);

// Matrix printing

void q_matrix_print(const q_matrix_t* m, const char* name);

#endif // FIX_POINT_MATRIX_H
