#ifndef FIX_POINT_MATRIX_H
#define FIX_POINT_MATRIX_H
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "fix_point_math.h"
#define Q_FORMAT_CUSTOM 16
#define Q_FORMAT Q_FORMAT_CUSTOM

//TODO: Implement the matrix using fixed point numbers

#define Q_MATRIX_AT(m, i, j) ((m)->elements[(i) * (m)->stride + (j)])
#define Q_MATRIX_PRINT(m) q_matrix_print((m), (#m))

struct matrix_t {
    size_t rows;
    size_t cols;
    size_t stride;
    q_t* elements;
};

typedef struct matrix_t q_matrix_t;

q_matrix_t q_matrix_alloc(size_t rows, size_t cols);


void q_matrix_free(q_matrix_t* m);
void q_matrix_freeDeep(q_matrix_t* m);

void q_matrix_print(q_matrix_t* m, const char* name);

#endif // FIX_POINT_MATRIX_H