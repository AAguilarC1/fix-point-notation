#include "../include/fix_point_matrix.h"

/**
 * @brief This function allocates memory for a matrix of fixed point numbers with the specified number of rows and columns.
 * 
 * @param rows The number of rows in the matrix
 * @param cols The number of columns in the matrix
 * @return q_matrix_t The matrix of fixed point numbers
 */
q_matrix_t q_matrix_alloc(size_t rows, size_t cols)
{
    assert((rows > 0) && "Number of rows must be greater than 0");
    assert((cols > 0) && "Number of columns must be greater than 0");

    q_matrix_t m;
    m.rows     = rows;
    m.cols     = cols;
    m.stride   = cols;
    m.elements = (q_t*) calloc(rows * cols, sizeof(q_t)); // Allocate memory for the matrix elements with 0 initialization
    assert((m.elements != NULL) && "Memory allocation failed"); // Check if the memory allocation was successful
    return m;
}

/**
 * @brief The function fills the matrix with a fixed point number of an specified value.
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param value The value to fill the matrix (fixed point number)
 */
void q_matrix_fill(const q_matrix_t* m, q_t value)
{
    Q_MATRIX_ASSERT(m);

    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = value;
        }
    }
}

/**
 * @brief The function fills the matrix with the identity matrix.
 * 
 * @param m The reference to the matrix of fixed point numbers to be filled with the identity matrix
 */
void q_matrix_identity(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);
    assert((m->rows == m->cols) && "Matrix is not square");

    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            if(i == j){
                Q_MATRIX_AT(m, i, j) = Q_ONE;
            } else {
                Q_MATRIX_AT(m, i, j) = Q_ZERO;
            }
        }
    }
}

/**
 * @brief This function sums two matrices of fixed point numbers and stores the result in the destination matrix.
 * @example 
 * q_matrix_t a = q_matrix_alloc(2, 2);
 * q_matrix_t b = q_matrix_alloc(2, 2);
 * q_ones(&a);
 * q_ones(&b);
 * q_matrix_sum(&a, &b);
 * Q_MATRIX_PRINT(&b);
 * 
 * Output:
 * &b: [
 *    2.000000, 2.000000,
 *   2.000000, 2.000000,
 * ]
 * 
 * @param src The reference to the source matrix of fixed point numbers
 * @param dst The reference to the destination matrix of fixed point numbers
 */
void q_matrix_sum(const q_matrix_t* src, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(src);
    Q_MATRIX_ASSERT(dst);

    assert((src->rows == dst->rows) && "Source and destination matrices have different number of rows");
    assert((src->cols == dst->cols) && "Source and destination matrices have different number of columns");

    for(size_t i = 0; i < src->rows; i++){
        for(size_t j = 0; j < src->cols; j++){
            Q_MATRIX_AT(dst, i, j) += Q_MATRIX_AT(src, i, j);
        }
    }
}

/**
 * @brief The function multiplies each element of the matrix by a scalar value in Q notation.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * q_matrix_scalar_mul(&m, float_to_q(2.0f));
 * Q_MATRIX_PRINT(&m);
 * 
 * Output:
 * &m: [
 *   2.000000, 2.000000,
 *  2.000000, 2.000000,
 * ]
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param scalar The scalar value in Q notation
 */
void q_matrix_scalar_mul(const q_matrix_t* m, q_t scalar)
{
    Q_MATRIX_ASSERT(m);

    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = q_product(Q_MATRIX_AT(m, i, j), scalar);
        }
    }
}

q_matrix_t q_matrix_dot_product(const q_matrix_t* a, const q_matrix_t* b)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);
    assert((a->cols == b->rows) && "The number of columns of the first matrix must be equal to the number of rows of the second matrix");

    q_matrix_t dst = q_matrix_alloc(a->rows, b->cols);
    size_t n = a->cols;
    q_zeros(&dst);

    for(size_t i = 0; i < dst.rows; i++){
        for(size_t j = 0; j < dst.cols; j++){
            for(size_t k = 0; k < n; k++){
                Q_MATRIX_AT(&dst, i, j) += q_product(Q_MATRIX_AT(a, i, k), Q_MATRIX_AT(b, k, j));
            }
        }
    }

    return dst;
}

/**
 * @brief The function copies the elements of the source matrix to the destination matrix.
 * 
 * @param src The reference to the source matrix of fixed point numbers
 * @param dst The reference to the destination matrix of fixed point numbers
 */
void q_matrix_cpy(const q_matrix_t* src, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(src);
    Q_MATRIX_ASSERT(dst);

    assert((src->rows == dst->rows) && "Source and destination matrices have different number of rows");
    assert((src->cols == dst->cols) && "Source and destination matrices have different number of columns");

    for(size_t i = 0; i < src->rows; i++){
        for(size_t j = 0; j < src->cols; j++){
            Q_MATRIX_AT(dst, i, j) = Q_MATRIX_AT(src, i, j);
        }
    }
}


/**
 * @brief This function frees the memory allocated for the matrix of fixed point numbers.
 * 
 * @param m The matrix of fixed point numbers
 */
void q_matrix_free(q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    m->rows = 0;
    m->cols = 0;
    m->stride = 0;
    free(m->elements);
    m->elements = NULL;
}

/**
 * @brief This function frees the memory allocated for the matrix of fixed point numbers and sets all the elements to 0.
 * 
 * @param m The matrix of fixed point numbers
 */
void q_matrix_freeDeep(q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = 0;
        }
    }
    q_matrix_free(m);
}

/**
 * @brief This function prints the matrix of fixed point numbers.
 * 
 * @param m The matrix of fixed point numbers
 * @param name The name of the matrix
 */
void q_matrix_print(const q_matrix_t* m, const char* name)
{
    Q_MATRIX_ASSERT(m);
    
    printf("%s: [\n", name);
    for(size_t i = 0; i < m->rows; i++){
        printf("\t");
        for(size_t j = 0; j < m->cols; j++){
            printf("%f, ", q_to_float(Q_MATRIX_AT(m, i, j)));
        }
        printf("\n");
    }
    printf("]\n");
}
