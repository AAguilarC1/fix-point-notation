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
 * @brief The function returns a slice of the matrix with the specified row
 * @details The row number starts from 0 to N-1, where N is the number of rows in the matrix. Meaning that the row index is zero-based.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_t dst = q_matrix_alloc(1, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * q_matrix_slice_row(&m, &dst, 0);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * dst: [
 * 2.000000, 1.000000,
 * ] 
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The slice of the matrix with the specified row
 * @param row The row number to slice
 */
void q_matrix_slice_row(const q_matrix_t* m, q_matrix_t* dst, size_t row)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert that the row index is within the bounds of the matrix
    assert((row < m->rows) && "Selected row index out of bounds for the row slice");
    
    // Assert that the destination matrix has the same number of columns as the source matrix
    assert((dst->cols == m->cols) && "Destination matrix has different number of columns for the row slice");

    for(size_t j = 0; j < m->cols; j++){
        Q_MATRIX_AT(dst, 0, j) = Q_MATRIX_AT(m, row, j);
    }
}

/**
 * @brief The following function returns a slice of the matrix with the specified column
 * @details The column number starts from 0 to N-1, where N is the number of columns in the matrix. Meaning that the column index is zero-based.
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The slice of the matrix with the specified column
 * @param col The column number to slice
 */
void q_matrix_slice_col(const q_matrix_t* m, q_matrix_t* dst, size_t col)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert that the column index is within the bounds of the matrix
    assert((col < m->cols) && "Selected column index out of bounds for the column slice");
    
    // Assert that the destination matrix has the same number of rows as the source matrix
    assert((dst->rows == m->rows) && "Destination matrix has different number of rows for the column slice");

    for(size_t i = 0; i < m->rows; i++){
        Q_MATRIX_AT(dst, i, 0) = Q_MATRIX_AT(m, i, col);
    }
}

/** @brief The function returns a submatrix of the matrix with the specified row and column
 * @details The row and column numbers start from 0 to N-1, where N is the number of rows or columns in the matrix. Meaning that the row and column index is zero-based.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(3, 3);
 * q_matrix_t dst = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_matrix_submatrix(&m, &dst, 0, 0);
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000, 1.000000,
 * 1.000000, 1.000000, 1.000000,
 * 1.000000, 1.000000, 1.000000,
 * ]
 * 
 * dst: [
 * 1.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The submatrix of the matrix with the specified row and column
 * @param row The row number to slice
 * @param col The column number to slice
 */
void q_matrix_submatrix(const q_matrix_t* m, q_matrix_t* dst, size_t row, size_t col)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert that the row index and the column index is within the bounds of the matrix
    assert((row < m->rows) && "Selected row index out of bounds for the submatrix");
    assert((col < m->cols) && "Selected column index out of bounds for the submatrix");

    // Assert the dimensions of the destination matrix
    assert((dst->rows == m->rows - 1) && "Destination matrix has an invalid number of rows for the submatrix");
    assert((dst->cols == m->cols - 1) && "Destination matrix has an invalid number of columns for the submatrix");

    // n represents the row index and k represents the column index for the destination matrix
    size_t n = 0, k = 0; // Initialize the indexes for the destination matrix 

    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = 0; j < m->cols; j++)
        {
            if(i != row && j != col)
            {
                Q_MATRIX_AT(dst, n, k) = Q_MATRIX_AT(m, i, j);
                k++;
                if(k == dst->cols)
                {
                    k = 0;
                    n++;
                }
            }
        }
    }

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
 * @details The identity matrix is a square matrix in which all the elements of the principal diagonal are ones and all other elements are zeros.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_identity(&m);
 * Q_MATRIX_PRINT(m);
 * 
 * Output:
 * m: [
 *  1.000000, 0.000000,
 * 0.000000, 1.000000,
 * ]
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
 * @brief The function fills the matrix with random fixed point numbers in the specified range (min, max).
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_fill_rand(&m, float_to_q(-1.0f), float_to_q(1.0f));
 * Q_MATRIX_PRINT(m);
 * 
 * Output:
 * m: [
 * 0.14134, -0.123523,
 * 0.5425213, -0.5432346,
 * ]
 * 
 * @param m The matrix to be filled with random fixed point numbers
 * @param min The minimum value of the random fixed point number
 * @param max The maximum value of the random fixed point number
 */
void q_matrix_fill_rand(const q_matrix_t* m, q_t min, q_t max)
{
    Q_MATRIX_ASSERT(m);
    srand(time(NULL));
    
    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = q_rand(min, max);
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
 * q_matrix_sum(&a, &b, &b);
 * Q_MATRIX_PRINT(b);
 * 
 * Output:
 * b: [
 *    2.000000, 2.000000,
 *   2.000000, 2.000000,
 * ]
 *
 * @param a The reference to matrix A of fixed point numbers
 * @param b The reference to matrix B of fixed point numbers 
 * @param dst The reference to the destination matrix of fixed point numbers
 */
void q_matrix_sum(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(dst);

    // Assert the dimensions of the matrices
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows");
    assert((a->cols == dst->cols) && "Source and destination matrices have different number of columns");
    assert((a->rows == b->rows) && "Matrices have different number of rows");
    assert((a->cols == b->cols) && "Matrices have different number of columns");

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->cols; j++){
            Q_MATRIX_AT(dst, i, j) = Q_MATRIX_AT(a, i, j) + Q_MATRIX_AT(b, i, j);
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
 * Q_MATRIX_PRINT(m);
 * 
 * Output:
 * m: [
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

/**
 * @brief The function multiplies each element on their respective position. A .* B = dst
 * @details The matrices must have the same number of rows and columns.
 * 
 * @example
 * q_matrix_t a = q_matrix_alloc(2, 2);
 * q_matrix_t b = q_matrix_alloc(2, 2);
 * q_matrix_t dst = q_matrix_alloc(2, 2);
 * q_ones(&a);
 * q_matrix_fill_float(&b, 2.0f);
 * q_matrix_elementwise_mul(&a, &b, &dst);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * dst: [
 * 2.000000, 2.000000,
 * 2.000000, 2.000000,
 * ]
 * 
 * @param a The reference to matrix A of fixed point numbers
 * @param b The reference to matrix B of fixed point numbers
 * @param dst The resulting matrix of the element-wise multiplication
 */
void q_matrix_elementwise_mul(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(dst);

    assert((a->rows == b->rows) && "Matrices have different number of rows");
    assert((a->cols == b->cols) && "Matrices have different number of columns");
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows");
    assert((a->cols == dst->cols) && "Source and destination matrices have different number of columns");

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->cols; j++){
            Q_MATRIX_AT(dst, i, j) = q_product(Q_MATRIX_AT(a, i, j), Q_MATRIX_AT(b, i, j));
        }
    }
}

/**
 * @brief The function computes the dot product of two matrices of fixed point numbers.
 * @details The number of columns of the first matrix must be equal to the number of rows of the second matrix.
 * 
 * @param a The reference to matrix A of fixed point numbers
 * @param b The reference to matrix B of fixed point numbers
 * @param dst The resulting matrix of the dot product
 * 
 * @example
 * q_matrix_t a = q_matrix_alloc(2, 2);
 * q_matrix_t b = q_matrix_alloc(2, 2);
 * q_matrix_t c = q_matrix_alloc(2, 2);
 * q_ones(&a);
 * q_ones(&b);
 * q_matrix_dot_product(&a, &b, &c);
 * Q_MATRIX_PRINT(c);
 * 
 * Output:
 * c: [
 *  2.000000, 2.000000,
 * 2.000000, 2.000000,
 * ]
 * 
 * Explanation:
 * A = [
 * 1.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * B = [
 * 1.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * C = A * B
 * 
 * C: [
 * (A[0][0] * B[0][0] + A[0][1] * B[1][0]), (A[0][0] * B[0][1] + A[0][1] * B[1][1]), 
 * (A[1][0] * B[0][0] + A[1][1] * B[1][0]), (A[1][0] * B[0][1] + A[1][1] * B[1][1]),
 * ]
 * 
 * C = [
 * 2.000000, 2.000000,
 * 2.000000, 2.000000,
 * ]
 * 
 */
void q_matrix_dot_product(const q_matrix_t* a, const q_matrix_t* b, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(dst);

    // Assert the dimensions of the matrices
    assert((a->cols == b->rows) && "The number of columns of the first matrix must be equal to the number of rows of the second matrix");
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows");
    assert((b->cols == dst->cols) && "Source and destination matrices have different number of columns");

    size_t n = a->cols;
    q_zeros(dst); // Fill destination matrix with 0

    for(size_t i = 0; i < dst->rows; i++){
        for(size_t j = 0; j < dst->cols; j++){
            for(size_t k = 0; k < n; k++){
                Q_MATRIX_AT(dst, i, j) += q_product(Q_MATRIX_AT(a, i, k), Q_MATRIX_AT(b, k, j));
            }
        }
    }
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
