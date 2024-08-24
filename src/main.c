#include <stdio.h>
#include "../include/fix_point_matrix.h"

int main() {
    q_matrix_t m = q_matrix_alloc(2, 2);
    Q_MATRIX_AT(&m, 0, 0) = float_to_q(1.15783f);
    Q_MATRIX_AT(&m, 0, 1) = float_to_q(2.183f);
    Q_MATRIX_AT(&m, 1, 0) = float_to_q(3.1f);
    Q_MATRIX_AT(&m, 1, 1) = float_to_q(42.0f);

    Q_MATRIX_PRINT(&m);
    q_matrix_freeDeep(&m);

    return 0;
}
