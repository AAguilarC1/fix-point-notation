#include "../include/fix_point_matrix.h"

// MARK: Matrix allocation

/**
 * @brief This function allocates memory for a matrix of fixed point numbers with the specified number of rows and columns.
 * 
 * @param rows The number of rows in the matrix
 * @param cols The number of columns in the matrix
 * @return q_matrix_t The matrix of fixed point numbers
 */
q_matrix_t q_matrix_alloc(size_t rows, size_t cols)
{
    assert((rows > 0) && "Number of rows must be greater than 0 when allocating a matrix");
    assert((cols > 0) && "Number of columns must be greater than 0 when allocating a matrix");

    q_matrix_t m;
    m.rows     = rows;
    m.cols     = cols;
    m.stride   = cols;
    m.elements = (q_t*) calloc(rows * cols, sizeof(q_t)); // Allocate memory for the matrix elements with 0 initialization
    assert((m.elements != NULL) && "Memory allocation failed"); // Check if the memory allocation was successful
    return m;
}

// MARK: Matrix manipulation

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
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
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
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_t dst = q_matrix_alloc(2, 1);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_matrix_slice_col(&m, &dst, 0);
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m : [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * dst: [
 * 2.000000,
 * 1.000000,
 * ]
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
 * @brief The function transposes the matrix of fixed point numbers and stores the result in the destination matrix.
 * 
 * @details The transpose of a matrix is a new matrix whose rows are the columns of the original matrix and whose columns are the rows of the original matrix.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 3);
 * q_matrix_t dst = q_matrix_alloc(3, 2);
 * 
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_matrix_transpose(&m, &dst);
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000, 1.000000,
 * 1.000000, 1.000000, 1.000000,
 * ]
 * 
 * dst: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * @param m The original matrix of fixed point numbers
 * @param dst The destination matrix with the transposed matrix
 */
void q_matrix_transpose(const q_matrix_t* m, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert the dimensions of the matrices
    assert((m->rows == dst->cols) && "Destination matrix has different number of columns than the source matrix (Can not perform transpose)");
    assert((m->cols == dst->rows) && "Destination matrix has different number of rows than the source matrix (Can not perform transpose)");

    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = 0; j < m->cols; j++)
        {
            Q_MATRIX_AT(dst, j, i) = Q_MATRIX_AT(m, i, j);
        }
    }
}

/**
 * @brief This function changes the rows of the matrix m for two given rows in the destination matrix dst.
 * @details The row indexes are zero-based.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_t dst = q_matrix_alloc(2, 2);
 * 
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_matrix_switch_rows(&m, &dst, 0, 1);
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * dst: [
 * 1.000000, 1.000000,
 * 2.000000, 1.000000,
 * ]
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The output matrix with the switched rows
 * @param row1 The first row to switch
 * @param row2 The second row to switch
 */
void q_matrix_switch_rows(const q_matrix_t* m, q_matrix_t* dst, size_t row1, size_t row2)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert that the row indexes are within the bounds of the matrix
    assert((row1 < m->rows) && "Selected row index out of bounds for the row switch");
    assert((row2 < m->rows) && "Selected row index out of bounds for the row switch");

    // Assert dimensions of the matrices
    assert((m->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not switch rows)");
    assert((m->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not switch rows)");

    q_matrix_cpy(m, dst); // Copy the source matrix to the destination matrix

    for(size_t j = 0; j < m->cols; j++)
    {
        q_t temp = Q_MATRIX_AT(dst, row1, j);
        Q_MATRIX_AT(dst, row1, j) = Q_MATRIX_AT(dst, row2, j);
        Q_MATRIX_AT(dst, row2, j) = temp;
    }

}

/**
 * @brief This function switches the columns of the matrix m for two specified columns into the dst matrix.
 * @details The column indexes are zero-based. 
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_t dst = q_matrix_alloc(2, 2);
 * 
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_matrix_switch_cols(&m, &dst, 0, 1);
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(dst);
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * dst: [
 * 1.000000, 2.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The output matrix with the switched columns
 * @param col1 The first column to switch
 * @param col2 The second column to switch
 */
void q_matrix_switch_cols(const q_matrix_t* m, q_matrix_t* dst, size_t col1, size_t col2)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    // Assert that the column indexes are within the bounds of the matrix
    assert((col1 < m->cols) && "Selected column index out of bounds for the column switch");
    assert((col2 < m->cols) && "Selected column index out of bounds for the column switch");

    // Assert dimensions of the matrices
    assert((m->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not switch columns)");
    assert((m->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not switch columns)");

    q_matrix_cpy(m, dst); // Copy the source matrix to the destination matrix

    for(size_t i = 0; i < m->rows; i++)
    {
        q_t temp = Q_MATRIX_AT(dst, i, col1);
        Q_MATRIX_AT(dst, i, col1) = Q_MATRIX_AT(dst, i, col2);
        Q_MATRIX_AT(dst, i, col2) = temp;
    }

}

// MARK: Matrix filling
/**
 * @brief The function fills the matrix with a fixed point number of an specified value.
 * @details The function fills the matrix with the specified value in Q notation. If you want to use a float value as an input please use the macro q_matrix_fill_float(m, value).
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_matrix_fill(&m, float_to_q(2.0f));
 * Q_MATRIX_PRINT(m);
 * 
 * Output:
 * m: [
 * 2.000000, 2.000000,
 * 2.000000, 2.000000,
 * ]
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
    assert((m->rows == m->cols) && "Matrix is not square shape when filling the identity matrix");

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
 * @details The function fills the matrix with random fixed point numbers in the specified range (min, max). If you want to use a float value as an input please use the macro q_matrix_fill_rand_float(m, min, max).
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
    
    assert((min < max) && "Minimum value must be less than the maximum value when filling the matrix with random values");

    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = q_rand(min, max);
        }
    }
}

// MARK: Linear Algebra Operations

/**
* @brief The function computes the LU decomposition of the matrix of fixed point numbers.
* @details The LU decomposition is a method to factorize a matrix into the product of a lower triangular matrix and an upper * triangular matrix.
* 
* The LU decomposition is calculated as follows:
* A = L * U
* 
* where:
* A is the input matrix
* L is the lower triangular matrix
* U is the upper triangular matrix
* 
* The LU decomposition is calculated using the Doolittle algorithm.
* 
* The Doolittle algorithm calculates the LU decomposition of a matrix A as follows:
* 1. Set the diagonal elements of the lower triangular matrix to 1
* 2. Calculate the elements of the lower triangular matrix and the upper triangular matrix
* 3. The elements of the lower triangular matrix are calculated as follows:
*     L[i][j] = U[i][j] / U[i][i]
* 
* 4. The elements of the upper triangular matrix are calculated as follows:
*     U[j][k] = U[j][k] - L[j][i] * U[i][k]
* 
* 5. Repeat the process for all rows and columns of the matrix
* 6. The LU decomposition is complete when the upper triangular matrix is obtained
* 
* @example
* q_matrix_t m = q_matrix_alloc(3, 3);
* q_matrix_t L = q_matrix_alloc(3, 3);
* q_matrix_t U = q_matrix_alloc(3, 3);
* 
* q_ones(&m);
* Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
* Q_MATRIX_AT(&m, 0, 1) = float_to_q(3.0f);
* Q_MATRIX_AT(&m, 0, 2) = float_to_q(1.0f);
* Q_MATRIX_AT(&m, 1, 0) = float_to_q(4.0f);
* Q_MATRIX_AT(&m, 1, 1) = float_to_q(4.0f);
* Q_MATRIX_AT(&m, 1, 2) = float_to_q(2.0f);
* 
* q_matrix_LU_decomposition(&m, &L, &U);
* 
* Q_MATRIX_PRINT(m);
* Q_MATRIX_PRINT(L);
* Q_MATRIX_PRINT(U);
* 
* Output:
* m: [
* 2.000000, 3.000000, 1.000000,
* 4.000000, 4.000000, 2.000000,
* 1.000000, 1.000000, 1.000000,
* ]   
* 
* L: [
* 1.000000, 0.000000, 0.000000,
* 2.000000, 1.000000, 0.000000,
* 0.500000, 0.250000, 1.000000,
* ]
* 
* U: [
* 2.000000, 3.000000, 1.000000,
* 0.000000, -2.000000, 0.000000,
* 0.000000, 0.000000, 0.500000,
* ]
* 
* @param m The reference to the matrix of fixed point numbers to be decomposed
* @param L The reference to the lower triangular matrix of fixed point numbers
* @param U The reference to the upper triangular matrix of fixed point numbers
*/
void q_matrix_LU_decomposition(const q_matrix_t* m, q_matrix_t* L, q_matrix_t* U)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(L);
    Q_MATRIX_ASSERT(U);

    assert((m->rows == m->cols) && "Matrix is not square shape when performing LU decomposition");
    assert((L->rows == m->rows) && "Matrix L has different number of rows than the input matrix");
    assert((L->cols == m->cols) && "Matrix L has different number of columns than the input matrix");
    assert((U->rows == m->rows) && "Matrix U has different number of rows than the input matrix");
    assert((U->cols == m->cols) && "Matrix U has different number of columns than the input matrix");

    q_matrix_cpy(m, U); // Copy the input matrix to the upper triangular matrix
    q_matrix_identity(L); // Fill the lower triangular matrix with the identity matrix

    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = i + 1; j < m->rows; j++)
        {
            // Calculate the elements of the lower triangular matrix
            /*
            L[i][j] = U[i][j] / U[i][i]
            */
            // If the diagonal element is zero, the matrix is singular
                // In this case, the LU decomposition is not possible
            assert((Q_MATRIX_AT(U, i, i) != Q_ZERO) && "Matrix is singular (LU decomposition is not possible)");

            Q_MATRIX_AT(L, j, i) = q_division(Q_MATRIX_AT(U, j, i), Q_MATRIX_AT(U, i, i));
            for(size_t k = i; k < m->rows; k++)
            {
                // Calculate the elements of the upper triangular matrix
                /*
                U[j][k] = U[j][k] - L[j][i] * U[i][k]
                */
                Q_MATRIX_AT(U, j, k) = Q_MATRIX_AT(U, j, k) - q_product(Q_MATRIX_AT(L, j, i), Q_MATRIX_AT(U, i, k));
            }
        }
    }

}

/**
 * @brief The function computes the PLU decomposition of the matrix of fixed point numbers. 
 * @details The PLU decomposition is a method to factorize a matrix into the product of a permutation matrix, a lower triangular matrix, and an upper triangular matrix.
 * Where the permutation matrix is a matrix that reorders the rows of the matrix, the lower triangular matrix is a matrix with ones on the diagonal and zeros above the diagonal, and the upper triangular matrix is a matrix with zeros below the diagonal.
 * 
 * The PLU decomposition is the product of the permutation matrix, the lower triangular matrix, and the upper triangular matrix.
 * A = P * L * U
 * 
 * where:
 * A is the input matrix
 * P is the permutation matrix
 * L is the lower triangular matrix
 * U is the upper triangular matrix
 * 
 * The PLU decomposition is calculated using the Doolittle algorithm.
 *
 * @example:
 * q_matrix_t m = q_matrix_alloc(3, 3);
 * q_matrix_t P = q_matrix_alloc(3, 3);
 * q_matrix_t L = q_matrix_alloc(3, 3);
 * q_matrix_t U = q_matrix_alloc(3, 3);
 * 
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) =  Q_ZERO;
 * Q_MATRIX_AT(&m, 0, 1) = float_to_q(3.0f);
 * Q_MATRIX_AT(&m, 0, 2) = float_to_q(1.0f);
 * Q_MATRIX_AT(&m, 1, 0) = float_to_q(4.0f);
 * Q_MATRIX_AT(&m, 1, 1) = float_to_q(4.0f);
 * Q_MATRIX_AT(&m, 1, 2) = float_to_q(2.0f);
 * 
 * q_matrix_PLU_decomposition(&m, &P, &L, &U);
 * q_matrix_t LU = q_matrix_alloc(3, 3);
 * q_matrix_dot_product(&L, &U, &LU);
 * 
 * Q_MATRIX_PRINT(m);
 * Q_MATRIX_PRINT(P);
 * Q_MATRIX_PRINT(LU);
 * 
 * q_matrix_t m2 = q_matrix_alloc(3, 3);
 * q_matrix_dot_product(&P, &LU, &m2);
 * Q_MATRIX_PRINT(m2);
 * 
 * Output:
 * m: [
 * 0.000000, 3.000000, 1.000000,
 * 4.000000, 4.000000, 2.000000,
 * 1.000000, 1.000000, 1.000000,
 * ]
 * 
 * P: [
 * 0.000000, 1.000000, 0.000000,
 * 1.000000, 0.000000, 0.000000,
 * 0.000000, 0.000000, 1.000000,
 * ]
 * 
 * LU: [
 * 4.000000, 4.000000, 2.000000,
 * 0.000000, 3.000000, 1.000000,
 * 0.000000, 0.000000, 1.000000,
 * ]
 * 
 * m2: [
 * 0.000000, 3.000000, 1.000000,
 * 4.000000, 4.000000, 2.000000,
 * 0.000000, 0.000000, 1.000000,
 * ]
 * 
 * @param m The reference to the matrix of fixed point numbers to be decomposed
 * @param P The reference to the permutation matrix of fixed point numbers
 * @param L The reference to the lower triangular matrix of fixed point numbers
 * @param U The reference to the upper triangular matrix of fixed point numbers
 */
void q_matrix_PLU_decomposition(const q_matrix_t* m , q_matrix_t* P, q_matrix_t* L, q_matrix_t* U)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(P);
    Q_MATRIX_ASSERT(L);
    Q_MATRIX_ASSERT(U);

    q_matrix_t temp = q_matrix_alloc(m->rows, m->cols);
    q_matrix_identity(P); // Fill the permutation matrix with the identity matrix
    q_matrix_identity(L); // Fill the lower triangular matrix with the identity matrix    
    q_matrix_cpy(m, U); // Copy the input matrix to the upper triangular matrix
    q_matrix_cpy(m, &temp); // Copy the input matrix to the temporary matrix

    for(size_t i = 0; i < m->rows; i++)
    {
        // Find the pivot element
        size_t max_idx = i;
        q_t max_val = q_absolute(Q_MATRIX_AT(U, max_idx, i));

        for(size_t j = i; j < m->cols; j++)
        {
            q_t val = q_absolute(Q_MATRIX_AT(U, j, i));
            if(val > max_val)
            {
                max_val = val;
                max_idx = j;
            }
        }

        // Swap the rows of the permutation matrix
        q_matrix_switch_rows(P, P, i, max_idx);
        q_matrix_switch_rows(U, U, i, max_idx);
        q_matrix_switch_rows(&temp, &temp, i, max_idx);

        q_matrix_LU_decomposition(&temp, L, U);

    }
    
    q_matrix_free(&temp);

}

/**
 * @brief The function computes the forward substitution of the matrix of fixed point numbers.
 * @details The forward substitution is a method to solve a system of linear equations using the LU decomposition.
 * 
 * The forward substitution is calculated as follows:
 * L * Y = b
 * 
 * where:
 * L is the lower triangular matrix of the LU decomposition
 * Y is the intermediate vector
 * b is the output vector of the system of linear equations
 * 
 * The forward substitution is calculated using the following steps:
 * 1. Initialize the intermediate vector Y with zeros
 * 2. Calculate the elements of the intermediate vector Y
 * 3. The elements of the intermediate vector Y are calculated as follows:
 *    Y[i] = b[i] - sum(L[i][j] * Y[j]) for j = 0 to i (where i is the row index)
 *    Y[i] = Y[i] / L[i][i]
 * 
 * @param L The reference to the lower triangular matrix of fixed point numbers
 * @param b The reference to the output vector of fixed point numbers
 * @param Y The reference to the intermediate vector of fixed point numbers
 */
void q_matrix_forward_substitution(const q_matrix_t* L, const q_matrix_t* b, const q_matrix_t* Y)
{
    Q_MATRIX_ASSERT(L);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(Y);

    assert((L->rows == L->cols) && "Matrix L is not square shape when performing forward substitution");

    assert((L->rows == b->rows) && "Matrix L and b have different number of rows (Can not perform forward substitution)");
    assert((b->cols == 1) && "Matrix b is not a column vector (Can not perform forward substitution)");

    assert((Y->rows == b->rows) && "Destination matrix and b have different number of rows (Can not perform forward substitution)");
    assert((Y->cols == 1) && "Destination matrix is not a column vector (Can not perform forward substitution)");

    q_zeros(Y); // Fill the X vector with zeros

    for(int i = 0; i < L->rows; i++)
    {
        q_t temp = Q_ZERO;
        for(int j = 0; j < i; j++)
        {
            temp += q_product(Q_MATRIX_AT(L, i, j), Q_MATRIX_AT(Y, j, 0));
        }

        temp = Q_MATRIX_AT(b, i, 0) - temp;
        Q_MATRIX_AT(Y, i, 0) = q_division(temp, Q_MATRIX_AT(L, i, i));

    }

}

/**
 * @brief The function computes the back substitution of the matrix of fixed point numbers.
 * @details The back substitution is a method to solve a system of linear equations using the LU decomposition.
 * 
 * The back substitution is calculated as follows:
 * U * X = Y
 * 
 * where:
 * U is the upper triangular matrix of the LU decomposition
 * X is the solution vector
 * Y is the intermediate vector
 * 
 * The back substitution is calculated using the following steps:
 * 1. Initialize the solution vector X with zeros
 * 2. Calculate the elements of the solution vector X
 * 3. The elements of the solution vector X are calculated as follows:
 *   X[i] = Y[i] - sum(U[i][j] * X[j]) for j = i to n (where n is the number of columns)
 *   X[i] = X[i] / U[i][i]
 * 
 * @param U The reference to the upper triangular matrix of fixed point numbers
 * @param Y The reference to the intermediate vector of fixed point numbers
 * @param X The reference to the solution vector of fixed point numbers
 */
void q_matrix_back_substitution(const q_matrix_t* U, const q_matrix_t* Y, const q_matrix_t* X)
{
    Q_MATRIX_ASSERT(U);
    Q_MATRIX_ASSERT(Y);
    Q_MATRIX_ASSERT(X);

    assert((U->rows == U->cols) && "Matrix U is not square shape when performing back substitution");

    assert((U->rows == Y->rows) && "Matrix U and Y have different number of rows (Can not perform back substitution)");
    assert((Y->cols == 1) && "Matrix Y is not a column vector (Can not perform back substitution)");

    assert((X->rows == Y->rows) && "Destination matrix and Y have different number of rows (Can not perform back substitution)");
    assert((X->cols == 1) && "Destination matrix is not a column vector (Can not perform back substitution)");

    q_zeros(X); // Fill the X vector with zeros

    for(int i = U->rows - 1; i >= 0; i--)
    {
        q_t temp = Q_ZERO;
        for(int j = i; j < U->cols; j++)
        {
            temp += q_product(Q_MATRIX_AT(U, i, j), Q_MATRIX_AT(X, j, 0));
        }

        temp = Q_MATRIX_AT(Y, i, 0) - temp;
        Q_MATRIX_AT(X, i, 0) = q_division(temp, Q_MATRIX_AT(U, i, i));

    }
}

/**
 * @brief This function solves a system of linear equations using the LU decomposition. 
 * @attention is important to note that the LU decomposition is only possible if the matrix is non-singular.
 * @details The system of linear equations is solved using the LU decomposition. The LU decomposition is calculated using the Doolittle algorithm. 
 * 
 * The system of linear equations is solved as follows:
 * A * X = b
 * 
 * where:
 * A is the input matrix
 * X is the solution vector
 * b is the output vector
 * 
 * The LU decomposition is calculated as follows:
 * A = L * U
 * 
 * Therefore, the system of linear equations can be solved as follows:
 * L * U * X = b
 * 
 * The system of linear equations is solved using forward substitution and back substitution.
 * 
 * The forward substitution is calculated as follows:
 * L * Y = b
 * 
 * The back substitution is calculated as follows:
 * U * X = Y
 * 
 * The solution vector X is obtained by solving the system of linear equations.
 * 
 * 
 * @param L The lower triangular matrix of the LU decomposition
 * @param U The upper triangular matrix of the LU decomposition
 * @param b The output vector of the system of linear equations
 * @param X The solution vector of the system of linear equations
 */
void q_matrix_LU_solve(const q_matrix_t* L, const q_matrix_t* U, const q_matrix_t* b, const q_matrix_t* X)
{
    Q_MATRIX_ASSERT(L); 
    Q_MATRIX_ASSERT(U);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(X);

    assert((L->rows == L->cols) && "Matrix L is not square shape when solving the system of linear equations");
    assert((U->rows == U->cols) && "Matrix U is not square shape when solving the system of linear equations");

    assert((L->rows == U->rows) && "Matrix L and U have different number of rows when solving the system of linear equations");
    
    assert((L->rows == b->rows) && "Matrix L and b have different number of rows when solving the system of linear equations");
    assert((b->cols == 1) && "Matrix b is not a column vector when solving the system of linear equations");

    assert((X->rows == b->rows) && "The solution matrix and b have different number of rows when solving the system of linear equations");
    assert((X->cols == 1) && "The solution matrix is not a column vector when solving the system of linear equations");

    q_matrix_t Y = q_matrix_alloc(b->rows, b->cols); // Allocate the Y vector

    q_matrix_forward_substitution(L, b, &Y); // Perform forward substitution
    q_matrix_back_substitution(U, &Y, X); // Perform back substitution

    q_matrix_free(&Y); // Free the Y vector
    
}

/**
 * @brief This function solves a system of linear equations using the PLU decomposition.
 * @details The system of linear equations is solved using the PLU decomposition. The PLU decomposition is calculated using the Doolittle algorithm.
 * 
 * The system of linear equations is solved as follows:
 * A * X = b
 * 
 * where:
 * A is the input matrix
 * X is the solution vector
 * b is the output vector
 * 
 * The PLU decomposition is calculated as follows:
 * A = P * L * U
 * 
 * Therefore, the system of linear equations can be solved as follows:
 * P * L * U * X = b
 * 
 * The system of linear equations is solved using forward substitution and back substitution.
 * 
 * The forward substitution is calculated as follows:
 * L * Y = P * b
 * 
 * The back substitution is calculated as follows:
 * U * X = Y
 * 
 * The solution vector X is obtained by solving the system of linear equations.
 * 
 * @param L The lower triangular matrix of the PLU decomposition
 * @param U The upper triangular matrix of the PLU decomposition
 * @param P The permutation matrix of the PLU decomposition
 * @param b The output vector of the system of linear equations
 * @param X The solution vector of the system of linear equations
 */
void q_matrix_LUP_solve(const q_matrix_t* L, const q_matrix_t* U, const q_matrix_t* P, const q_matrix_t* b, const q_matrix_t* X)
{
    Q_MATRIX_ASSERT(L); 
    Q_MATRIX_ASSERT(U);
    Q_MATRIX_ASSERT(P);
    Q_MATRIX_ASSERT(b);
    Q_MATRIX_ASSERT(X);

    assert((L->rows == L->cols) && "Matrix L is not square shape when solving the system of linear equations");
    assert((U->rows == U->cols) && "Matrix U is not square shape when solving the system of linear equations");
    assert((P->rows == P->cols) && "Matrix P is not square shape when solving the system of linear equations");

    assert((L->rows == U->rows) && "Matrix L and U have different number of rows when solving the system of linear equations");
    assert((L->rows == P->rows) && "Matrix L and P have different number of rows when solving the system of linear equations");

    assert((L->rows == b->rows) && "Matrix L and b have different number of rows when solving the system of linear equations");
    assert((b->cols == 1) && "Matrix b is not a column vector when solving the system of linear equations");

    assert((X->rows == b->rows) && "Destination matrix and b have different number of rows when solving the system of linear equations");
    assert((X->cols == 1) && "Destination matrix is not a column vector when solving the system of linear equations");

    q_matrix_t z = q_matrix_alloc(b->rows, b->cols); // Allocate the z vector
    q_matrix_dot_product(P, b, &z); // Perform the dot product between the permutation matrix and the b vector

    q_matrix_LU_solve(L, U, &z, X); // Solve the system of linear equations using the LU decomposition

    q_matrix_free(&z); // Free the z vector

}

/**
 * @brief This function computes the inverse of a matrix using the PLU decomposition.
 * @details The matrix must be square shape to calculate the inverse. The inverse of a matrix is calculated using the PLU decomposition.
 * The inverse of a matrix is the matrix that results in the identity matrix when multiplied by the original matrix.
 * 
 * The inverse of a matrix is calculated as follows:
 * A * A^-1 = I
 * 
 * If we assume that:
 * A * X = b 
 * 
 * where: 
 * b = I
 * 
 * Then,
 * A * X = I
 * 
 * If we perform the PLU decomposition of the matrix:
 * A = P *L * U
 * P * L * U * X = I
 * 
 * And we assume that:
 * X = A^-1
 * 
 * By solving the system of linear equations, the inverse of the matrix can be calculated.
 * X = U^-1 * L^-1 * P^-1 = U^-1 * L^-1 * P^T
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @param dst The resulting inverse matrix of the input matrix  
 */
void q_matrix_inverse(const q_matrix_t* m, q_matrix_t* dst)
{
    Q_MATRIX_ASSERT(m);
    Q_MATRIX_ASSERT(dst);

    assert((m->rows == m->cols) && "Matrix is not square shape when calculating the inverse");

    q_matrix_t L = q_matrix_square_alloc(m->rows); // Allocate the lower triangular matrix
    q_matrix_t U = q_matrix_square_alloc(m->rows); // Allocate the upper triangular matrix
    q_matrix_t P = q_matrix_square_alloc(m->rows); // Allocate the permutation matrix

    q_matrix_PLU_decomposition(m, &P, &L, &U); // Compute the PLU decomposition of the matrix

    q_matrix_t I = q_matrix_square_alloc(m->rows); // Allocate the identity matrix
    q_matrix_identity(&I); // Fill the identity matrix with the identity matrix

    q_matrix_t X = q_matrix_alloc(m->rows, 1); // Allocate the X vector
    q_matrix_t b = q_matrix_alloc(m->rows, 1); // Allocate the b vector

    for(size_t i = 0; i < m->cols; i++)
    {
        q_matrix_slice_col(&I, &b, i); // Slice the i-th column of the identity matrix
        
        q_matrix_LUP_solve(&L, &U, &P, &b, &X); // Solve the system of linear equations

        for(size_t j = 0; j < m->rows; j++)
        {
            Q_MATRIX_AT(dst, j, i) = Q_MATRIX_AT(&X, j, 0);
        }

    }

    q_matrix_freeDeep(&b); // Free the b vector
    q_matrix_freeDeep(&X); // Free the X vector
    q_matrix_freeDeep(&I); // Free the identity matrix
    q_matrix_freeDeep(&P); // Free the permutation matrix
    q_matrix_freeDeep(&U); // Free the upper triangular matrix
    q_matrix_freeDeep(&L); // Free the lower triangular matrix

    return;
}

// MARK: Basic Matrix Operations

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
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not perform sum)");
    assert((a->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not perform sum)");
    assert((a->rows == b->rows) && "Matrices have different number of rows (Can not perform sum)");
    assert((a->cols == b->cols) && "Matrices have different number of columns (Can not perform sum)");

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->cols; j++){
            Q_MATRIX_AT(dst, i, j) = Q_ZERO;
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

    assert((a->rows == b->rows) && "Matrices have different number of rows (Can not perform element-wise multiplication)");
    assert((a->cols == b->cols) && "Matrices have different number of columns (Can not perform element-wise multiplication)");
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not perform element-wise multiplication)");
    assert((a->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not perform element-wise multiplication)");

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->cols; j++){
            Q_MATRIX_AT(dst, i, j) = Q_ZERO;
            Q_MATRIX_AT(dst, i, j) = q_product(Q_MATRIX_AT(a, i, j), Q_MATRIX_AT(b, i, j));
        }
    }
}

// MARK: Matrix Properties

/**
 * @brief The function computes the determinant of the matrix of fixed point numbers. 
 * @details The matrix must be square shape to calculate the determinant. The determinant is calculated using the LU decomposition. 
 * The determinant is calculated as follows: 
 * det(A) = det(L) * det(U) = det(U)
 * 
 * where:
 * A is the input matrix
 * L is the lower triangular matrix
 * U is the upper triangular matrix
 * 
 * The determinant of the upper triangular matrix is the product of the diagonal elements.
 * 
 * @example 
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * q_t det = q_matrix_determinant(&m);
 * 
 * printf("Determinant: %f\n", q_to_float(det));
 * 
 * Output:
 * Determinant: 1.000000
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The determinant of the matrix
 */
q_t q_matrix_determinant(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    // Assert that the matrix is square shape
    assert((m->rows == m->cols) && "Matrix is not square shape when calculating the determinant");
    
    if(m->rows == 1)
    {
        return Q_MATRIX_AT(m, 0, 0);
    }

    if(m->rows == 2)
    {
        return q_product(Q_MATRIX_AT(m, 0, 0), Q_MATRIX_AT(m, 1, 1)) - q_product(Q_MATRIX_AT(m, 0, 1), Q_MATRIX_AT(m, 1, 0));
    }
    
    q_t ret = Q_ONE;

    q_matrix_t P = q_matrix_square_alloc(m->rows); // Allocate the permutation matrix
    q_matrix_t L = q_matrix_square_alloc(m->rows); // Allocate the lower triangular matrix
    q_matrix_t U = q_matrix_square_alloc(m->rows); // Allocate the upper triangular matrix

    q_matrix_PLU_decomposition(m, &P, &L, &U); // Compute the PLU decomposition of the matrix

    q_t sign = Q_MINUS_ONE;

    // Calculate the sign of the permutation matrix
    for(size_t i = 0; i < m->rows; i++)
    {
        /*
        The sign of the permutation matrix is calculated by counting the number of row swaps.
        If the number of row swaps is even, the sign is positive.
        If the number of row swaps is odd, the sign is negative.
        */
        if(Q_MATRIX_AT(&P, i, i) != INT_TO_Q(i))
        {
            sign = -sign;
        }
    }

    for(size_t i = 0; i < m->rows; i++)
    {
        /*
        The determinant of the upper triangular matrix is the product of the diagonal elements.
        det(U) = U[0][0] * U[1][1] * ... * U[n][n]
        */
        ret = q_product(ret, Q_MATRIX_AT(&U, i, i));
    }

    q_matrix_free(&L); // Free the lower triangular matrix
    q_matrix_free(&U); // Free the upper triangular matrix
    q_matrix_free(&P); // Free the permutation matrix
    
    return q_product(ret, sign);
    // return ret;
}


/**
 * @brief The function calculates the trace of the matrix of fixed point numbers. 
 * @details The trace of a square matrix is the sum of the principal diagonal elements of the matrix.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * q_t trace = q_matrix_trace(&m);
 * Q_MATRIX_PRINT(m);
 * 
 * printf("Trace: %f\n", q_to_float(trace));
 * 
 * Output:
 * m: [
 * 1.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * Trace: 2.000000
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The trace of the matrix
 */
q_t q_matrix_trace(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    assert((m->rows == m->cols) && "Matrix is not square shape when calculating the trace");

    q_t ret = Q_ZERO;

    for(size_t i = 0; i < m->rows; i++)
    {
        ret += Q_MATRIX_AT(m, i, i);
    }

    return ret;
}

/**
 * @brief Sum the contents of the matrix of fixed point numbers.
 * @details The function sums all the elements of the matrix and returns the result.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * q_t sum = q_matrix_sum_contents(&m);
 * 
 * printf("Sum: %f\n", q_to_float(sum));
 * 
 * Output:
 * Sum: 4.000000
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The resulting sum of the elements of the matrix
 */
q_t q_matrix_sum_contents(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    q_t ret = Q_ZERO;

    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = 0; j < m->cols; j++)
        {
            ret += Q_MATRIX_AT(m, i, j);
        }
    }

    return ret;
}

/**
 * @brief The 1-norm of a matrix is the maximum absolute column sum of the matrix. And then return the maximum value.
 * @details The 1-norm of a matrix is the maximum absolute column sum of the matrix. The 1-norm is calculated as follows:
 * 
 * ||A||_1 = max( sum( |A[i][j]| ) )
 * 
 * where:
 * A is the input matrix
 * i is the row index
 * j is the column index
 * 
 * The 1-norm is the maximum absolute column sum of the matrix.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * q_t norm = q_matrix_1_norm(&m);
 * 
 * Q_MATRIX_PRINT(m);
 * printf("1-norm: %f\n", q_to_float(norm));
 * 
 * Output:
 * m : [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * 1-norm: 3.000000
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The 1-norm of the matrix
 */
q_t q_matrix_1_norm(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    q_t ret = Q_ZERO;

    for(size_t i = 0; i < m->rows; i++)
    {
        q_t sum = Q_ZERO;

        for(size_t j = 0; j < m->cols; j++)
        {
            sum += q_absolute(Q_MATRIX_AT(m, i, j));
        }

        if(sum > ret)
        {
            ret = sum;
        }
    }

    return ret;
}

/**
 * @brief The infinity norm of a matrix is the maximum absolute row sum of the matrix. And then return the maximum value.
 * 
 * @details The infinity norm of a matrix is the maximum absolute row sum of the matrix. The infinity norm is calculated as follows:
 * 
 * ||A||_inf = max( sum( |A[i][j]| ) )
 * 
 * where:
 * A is the input matrix
 * i is the row index
 * j is the column index
 * 
 * The infinity norm is the maximum absolute row sum of the matrix.
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_t norm = q_matrix_infinity_norm(&m);
 * 
 * Q_MATRIX_PRINT(m);
 * printf("Infinity norm: %f\n", q_to_float(norm));
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * Infinity norm: 3.000000
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The infinity norm of the matrix
 */
q_t q_matrix_infinity_norm(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    q_t ret = Q_ZERO;

    for(size_t j = 0; j < m->cols; j++)
    {
        q_t sum = Q_ZERO;

        for(size_t i = 0; i < m->rows; i++)
        {
            sum += q_absolute(Q_MATRIX_AT(m, i, j));
        }

        if(sum > ret)
        {
            ret = sum;
        }
    }

    return ret;
}

/**
 * @brief The function computes the Euclidean norm of the matrix of fixed point numbers.
 * 
 * @details The Euclidean norm of a matrix is the square root of the sum of the squares of the elements of the matrix.
 * The Euclidean norm is calculated as follows:
 * 
 * ||A||_2 = sqrt( sum( A[i][j]^2 ) )
 * 
 * where:
 * A is the input matrix
 * i is the row index
 * j is the column index
 * 
 * @example
 * q_matrix_t m = q_matrix_alloc(2, 2);
 * q_ones(&m);
 * Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
 * 
 * q_t norm = q_matrix_euclidean_norm(&m);
 * 
 * Q_MATRIX_PRINT(m);
 * printf("Euclidean norm: %f\n", q_to_float(norm)); 
 * 
 * Output:
 * m: [
 * 2.000000, 1.000000,
 * 1.000000, 1.000000,
 * ]
 * 
 * Euclidean norm: 2.6457513110645907
 * 
 * @param m The reference to the matrix of fixed point numbers
 * @return q_t The Euclidean norm of the matrix
 */
q_t q_matrix_euclidean_norm(const q_matrix_t* m)
{
    Q_MATRIX_ASSERT(m);

    q_t ret = Q_ZERO;

    for(size_t i = 0; i < m->rows; i++)
    {
        for(size_t j = 0; j < m->cols; j++)
        {
            ret += q_int_power(Q_MATRIX_AT(m, i, j), 2);
        }
    }

    return q_sqrt(ret);
}

// MARK: Matrix Operations

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
    assert((a->cols == b->rows) && "The number of columns of the first matrix must be equal to the number of rows of the second matrix (Can not perform dot product)");
    assert((a->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not perform dot product)");
    assert((b->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not perform dot product)");

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

// MARK: Matrix validation

/**
 * @brief This function checks if two matrices have the same contents
 * @attention Do not use this function to compare floating-point numbers
 * 
 * @param a The reference to matrix A of fixed point numbers
 * @param b The reference to matrix B of fixed point numbers 
 * @return q_status_t Returns Q_MATRIX_OK if the matrices are equal, otherwise returns Q_MATRIX_ERROR
 */
q_status_t q_matrix_is_equal(const q_matrix_t* a, const q_matrix_t* b)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);

    if(a->rows != b->rows || a->cols != b->cols)
    {
        return Q_MATRIX_ERROR;
    }

    for(size_t i = 0; i < a->rows; i++)
    {
        for(size_t j = 0; j < a->cols; j++)
        {
            if(Q_MATRIX_AT(a, i, j) != Q_MATRIX_AT(b, i, j))
            {
                return Q_MATRIX_ERROR;
            }
        }
    }

    return Q_MATRIX_OK;
}

/**
 * @brief This function checks if two matrices are approximately equal within a tolerance value.
 * @details The function checks if the absolute difference between the elements of the matrices is less than the tolerance value.
 * 
 * @param a The reference to matrix A of fixed point numbers 
 * @param b The reference to matrix B of fixed point numbers
 * @param abs_tol The absolute tolerance value
 * @return q_status_t Returns Q_MATRIX_OK if the matrices are approximately equal, otherwise returns Q_MATRIX_ERROR
 */
q_status_t q_matrix_is_approx(const q_matrix_t* a, const q_matrix_t* b, q_t abs_tol)
{
    Q_MATRIX_ASSERT(a);
    Q_MATRIX_ASSERT(b);

    if(a->rows != b->rows || a->cols != b->cols)
    {
        return Q_MATRIX_ERROR;
    }

    for(size_t i = 0; i < a->rows; i++)
    {
        for(size_t j = 0; j < a->cols; j++)
        {
            if(q_absolute(Q_MATRIX_AT(a, i, j) - Q_MATRIX_AT(b, i, j)) > abs_tol)
            {
                return Q_MATRIX_ERROR;
            }
        }
    }

    return Q_MATRIX_OK;
}


// MARK: Matrix memory management

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

    assert((src->rows == dst->rows) && "Source and destination matrices have different number of rows (Can not perform copy)");
    assert((src->cols == dst->cols) && "Source and destination matrices have different number of columns (Can not perform copy)");

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

// MARK: Matrix visualization

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
