#ifndef TEST_Q_MATH_H
#define TEST_Q_MATH_H

#include "CUnit/Basic.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/fix_point_math.h"

void testProduct(void);
void testDivision(void);
void testAbsolute(void);
void testIntPower(void);
void test_q_sqrt(void);

void test_q_sin(void);
void test_q_cos(void);
void test_q_tan(void);
void test_q_sec(void);
void test_q_csc(void);
void test_q_cot(void);

void add_trigonometric_tests(CU_pSuite suite);
void add_general_math_tests(CU_pSuite suite);

#endif // TEST_Q_MATH_H
