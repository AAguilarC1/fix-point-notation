#include "../include/fix_point_matrix.h"

q_matrix_t q_matrix_alloc(size_t rows, size_t cols)
{
    q_matrix_t m;
    m.rows     = rows;
    m.cols     = cols;
    m.stride   = cols;
    m.elements = (q_t*) calloc(rows * cols, sizeof(q_t));
    assert((m.elements != NULL) && "Memory allocation failed");
    return m;
}

void q_matrix_free(q_matrix_t* m)
{
    m->rows = 0;
    m->cols = 0;
    m->stride = 0;
    free(m->elements);
}

void q_matrix_freeDeep(q_matrix_t* m){
    for(size_t i = 0; i < m->rows; i++){
        for(size_t j = 0; j < m->cols; j++){
            Q_MATRIX_AT(m, i, j) = 0;
        }
    }
    q_matrix_free(m);
}

void q_matrix_print(q_matrix_t* m, const char* name)
{
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
