#ifndef TEST_Q_MATRIX_H
#define TEST_Q_MATRIX_H
#include "CUnit/Basic.h"
#include "../include/fix_point_matrix.h"
//TODO: Implement the tests for the matrix of fixed point numbers

void test_q_matrix_alloc();
void test_q_fill();
void test_q_matrix_LU_decomposition();
void test_q_matrix_PLU_decomposition();
void test_q_matrix_inverse();

void add_matrix_tests(CU_pSuite suite);

#endif // TEST_Q_MATRIX_H
