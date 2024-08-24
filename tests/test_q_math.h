#ifndef TEST_Q_MATH_H
#define TEST_Q_MATH_H

#include "CUnit/Basic.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/fix_point_math.h"

void testProduct();
void testDivision();
void testAbsolute();
void testIntPower();
void test_q_sqrt();

void test_q_sin();
void test_q_cos();
void test_q_tan();
void test_q_sec();
void test_q_csc();
void test_q_cot();

void add_trigonometric_tests(CU_pSuite suite);
void add_general_math_tests(CU_pSuite suite);

#endif // TEST_Q_MATH_H
