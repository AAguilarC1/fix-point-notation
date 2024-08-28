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

    q_matrix_t m3 = q_matrix_alloc(2, 2); 
    q_matrix_dot_product(&m, &m2, &m3);
    Q_MATRIX_PRINT(m3);

    q_matrix_t m4 = q_matrix_alloc(1, 2);
    q_matrix_fill_float(&m4, 1.0f);
    q_matrix_t m5 = q_matrix_alloc(1, 2); 
    q_matrix_dot_product(&m4, &m3, &m5);    

    Q_MATRIX_PRINT(m5);

    q_matrix_t m6 = q_matrix_alloc(1, 2);
    q_matrix_fill_rand_float(&m6, -24.0f, 24.0f);
    Q_MATRIX_PRINT(m6);

    q_matrix_t m7 = q_matrix_alloc(1, 2);
    q_matrix_elementwise_mul(&m5, &m6, &m7);
    Q_MATRIX_PRINT(m7);

    uint8_t size = 3;
    q_matrix_t m8 = q_matrix_square_alloc(size);

    // q_matrix_fill_rand_float(&m8, -10.0f, 10.0f);
    Q_MATRIX_AT(&m8, 0, 0) = Q_ONE; // TODO: Research how to implement PLU so we avoind the issue with 0 value at the principal diagonal
    Q_MATRIX_AT(&m8, 0, 1) = float_to_q(2.656250f);
    Q_MATRIX_AT(&m8, 1, 0) = float_to_q(3.656921f);
    Q_MATRIX_AT(&m8, 1, 1) = float_to_q(8.850708f);
    Q_MATRIX_AT(&m8, 1, 2) = float_to_q(7.096252f);
    Q_MATRIX_AT(&m8, 2, 0) = float_to_q(-3.005981f);
    Q_MATRIX_AT(&m8, 2, 1) = Q_ZERO;
    Q_MATRIX_AT(&m8, 2, 2) = float_to_q(-9.760132f);

    Q_MATRIX_PRINT(m8);
    
    q_t det = q_matrix_determinant(&m8);
    printf("Determinant of 'm8': %f\n", q_to_float(det));
    
    q_matrix_freeDeep(&m);
    q_matrix_freeDeep(&m2);
    q_matrix_freeDeep(&m3);
    q_matrix_freeDeep(&m4);
    q_matrix_freeDeep(&m5);
    q_matrix_freeDeep(&m6);
    q_matrix_freeDeep(&m7);
    q_matrix_freeDeep(&m8);

    return 0;
}
