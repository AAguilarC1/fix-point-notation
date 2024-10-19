#include <stdio.h>
#include "../include/fix_point_complex.h"
#include "../include/fix_point_matrix.h"

int main(void) {
    uint8_t size = 2;
    q_matrix_t m = q_matrix_square_alloc(size);
    q_matrix_fill_rand_float(&m, -10.0f, 10.0f);
    // Q_MATRIX_AT(&m, 0, 0) = float_to_q(1.572f);
    // Q_MATRIX_AT(&m, 0, 1) = float_to_q(2.57f);
    // Q_MATRIX_AT(&m, 0, 2) = float_to_q(3.8902f);
    // Q_MATRIX_AT(&m, 1, 0) = float_to_q(-3.2f);
    // Q_MATRIX_AT(&m, 1, 1) = float_to_q(2.572f);
    // Q_MATRIX_AT(&m, 1, 2) = float_to_q(3.572f);
    // Q_MATRIX_AT(&m, 2, 0) = float_to_q(3.1532f);
    // Q_MATRIX_AT(&m, 2, 1) = float_to_q(0.1532f);
    // Q_MATRIX_AT(&m, 2, 2) = float_to_q(1.1532f);

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
