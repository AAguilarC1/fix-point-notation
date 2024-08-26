#include <stdio.h>
#include "../include/fix_point_matrix.h"

int main() {
    q_matrix_t m = q_matrix_alloc(2, 2);
    Q_MATRIX_AT(&m, 0, 0) = float_to_q(1.15783f);
    Q_MATRIX_AT(&m, 0, 1) = float_to_q(2.183f);
    Q_MATRIX_AT(&m, 1, 0) = float_to_q(3.1f);
    Q_MATRIX_AT(&m, 1, 1) = float_to_q(42.0f);
    Q_MATRIX_PRINT(m);

    q_matrix_fill_float(&m, 312.33f);
    Q_MATRIX_PRINT(m);

    q_zeros(&m);
    Q_MATRIX_PRINT(m);

    q_ones(&m);
    Q_MATRIX_PRINT(m);

    q_matrix_scalar_mul_float(&m, 3.14158f);
    Q_MATRIX_PRINT(m);

    q_matrix_t m2 = q_matrix_alloc(2, 2);
    q_matrix_fill_float(&m2, -3.0f);
    Q_MATRIX_AT(&m2, 1, 1) = float_to_q(-1.0f);

    Q_MATRIX_AT(&m, 0, 0) = float_to_q(2.0f);
    Q_MATRIX_AT(&m, 0, 1) = float_to_q(3.0f);
    Q_MATRIX_AT(&m, 1, 0) = float_to_q(4.1f);

    q_matrix_t m3 = q_matrix_dot_product(&m, &m2);
    Q_MATRIX_PRINT(m3);

    q_matrix_t m4 = q_matrix_alloc(1, 2);
    q_matrix_fill_float(&m4, 1.0f);
    q_matrix_t m5 = q_matrix_dot_product(&m4, &m3);    

    Q_MATRIX_PRINT(m5);

    q_matrix_freeDeep(&m);
    q_matrix_freeDeep(&m2);
    q_matrix_freeDeep(&m3);

    return 0;
}
