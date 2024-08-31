#include <stdio.h>
#include "../include/fix_point_matrix.h"

int main() {
    uint8_t size = 3;
    q_matrix_t m = q_matrix_square_alloc(size);
    q_matrix_fill_rand_float(&m, -10.0f, 10.0f);
    q_matrix_t L = q_matrix_square_alloc(size);
    q_matrix_t U = q_matrix_square_alloc(size);
    q_matrix_t P = q_matrix_square_alloc(size);

    q_matrix_PLU_decomposition(&m, &P, &L, &U);

    q_matrix_t LU = q_matrix_square_alloc(size);
    q_matrix_dot_product(&L, &U, &LU);

    q_matrix_t m2 = q_matrix_square_alloc(size);
    q_matrix_dot_product(&P, &LU, &m2);

    if (q_matrix_is_approx_float(&m, &m2, 0.001f) == Q_MATRIX_OK) {
        q_matrix_t m_inv = q_matrix_square_alloc(size);
        q_matrix_inverse(&m, &m_inv);

        q_matrix_t m2 = q_matrix_square_alloc(size);
        q_matrix_dot_product(&m, &m_inv, &m2);

        Q_MATRIX_PRINT(m);
        Q_MATRIX_PRINT(m_inv);
        Q_MATRIX_PRINT(m2);

        q_matrix_freeDeep(&m2);
        q_matrix_freeDeep(&m_inv);
    } else {
        Q_MATRIX_PRINT(m);
        Q_MATRIX_PRINT(m2);
        printf("The matrices are not equal\n");
    }

    q_matrix_freeDeep(&m);
    q_matrix_freeDeep(&L);
    q_matrix_freeDeep(&U);
    q_matrix_freeDeep(&P);
    q_matrix_freeDeep(&LU);

    return 0;
}
