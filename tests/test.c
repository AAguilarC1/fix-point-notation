#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/fix_point_math.h"

// Test case
// MARK: - Integer to Q format
const start_N = -1000;
const end_N = 1000;
void testIntToQ() {
    uint32_t N = end_N - start_N;
    for (int32_t i = 0; i < N; i++){
        int32_t x = start_N + i;
        q_t q_x = INT_TO_Q(x);
        CU_ASSERT_EQUAL(Q_TO_INT(q_x), x);
    }

}

// MARK: - Float to Q format
const float start_float = -1000.0;
const float end_float = 1000.0;
const uint16_t N_float = 1 << 12;

void testFloatToQ() {
    float range = end_float - start_float;
    float step = range / (N_float - 1);

    for (uint32_t i = 0; i < N_float; i++){
        float x = start_float + i * step;
        q_t q_x = float_to_q(x);
        CU_ASSERT_DOUBLE_EQUAL(x, q_to_float(q_x), 0.001);
    }
}

// MARK: - Product Q format
const float start_product = -1000.0;
const float end_product = 1000.0;
const uint16_t N_product = 1 << 8;

void testProduct() {

    srand((uint32_t) time(NULL));

    float range = end_product - start_product;
    float step = range / (N_product - 1);
    float amplitude = 10.0f;

    for (uint32_t i = 0; i < N_product; i++){
        float x = start_product + i * step;
        float y = ((float) rand() / (float) (RAND_MAX)) * (amplitude * 2) - amplitude;

        q_t a = float_to_q(x);
        q_t b = float_to_q(y);

        q_t c = q_product(a, b);

        CU_ASSERT_DOUBLE_EQUAL(x * y, q_to_float(c), 0.05);
    }

    float z = 0.0001234;
    float y = 0.25;
    float x = 0.5;

    q_t a = float_to_q(z);
    q_t b = INT_TO_Q(2);
    q_t c = q_product(a, b);
    
    a = float_to_q(y);
    c = q_product(a, c);
    
    b = float_to_q(x);
    c = q_product(b, c);

    CU_ASSERT_DOUBLE_EQUAL(z * 2 * 0.25 * 0.5, q_to_float(c), 0.001);
}

// MARK: - Division Q format
const float start_division = -1000.0;
const float end_division = 1000.0;
const uint16_t N_division = 1 << 8;

void testDivision(){
    srand((uint32_t) time(NULL));

    float range = end_division - start_division;
    float step = range / (N_division - 1);
    float amplitude = 1000.0f;

    for (uint32_t i = 0; i < N_division; i++){
        float x = ((float) rand() / (float) (RAND_MAX)) * (amplitude * 2) - amplitude;
        float y = start_division + i * step;

        q_t a = float_to_q(x);
        q_t b = float_to_q(y);

        q_t c = q_division(a, b);

        CU_ASSERT_DOUBLE_EQUAL(x / y, q_to_float(c), 0.05);
    }

    float z = 0.0001234;
    float y = 0.25;
    float x = 0.5;

    q_t a = float_to_q(z);
    q_t b = float_to_q(y);
    q_t c = q_division(a, b);

    a = float_to_q(x);
    c = q_division(c, a);

    CU_ASSERT_DOUBLE_EQUAL((z / y) / x, q_to_float(c), 0.001);

    a = INT_TO_Q(10000);
    b = INT_TO_Q(100);
    c = q_division(a, b);
    CU_ASSERT_EQUAL(Q_TO_INT(c), 100);

    a = INT_TO_Q(1);
    b = INT_TO_Q(1000);
    c = q_division(a, b);
    CU_ASSERT_DOUBLE_EQUAL(1 / (1000.0f), q_to_float(c), 0.001);
}

// MARK: - Absolute Q format
const float start_absolute = -1000.0;
const float end_absolute = 1000.0;
const uint16_t N_absolute = 1 << 8;

void testAbsolute(){
    float range = end_absolute - start_absolute;
    float step = range / (N_absolute - 1);

    for (uint32_t i = 0; i < N_absolute; i++){
        float x = start_absolute + i * step;
        q_t a = float_to_q(x);
        q_t b = q_absolute(a);

        CU_ASSERT_DOUBLE_EQUAL(fabs(x), q_to_float(b), 0.001);
    }
}

// MARK: - Int Power Q format
const uint16_t N_power = 5;
void testIntPower()
{
    float start_power = -5.0f;
    float end_power = 5.0f;
    float range = end_power - start_power;
    float step = range / (N_power - 1);

    for(int32_t i = 0; i < N_power; i++){
        float x = start_power + i * step;
        q_t a = float_to_q(x);
        q_t b = q_int_power(a, i);

        CU_ASSERT_DOUBLE_EQUAL(pow(x, i), q_to_float(b), 0.001);
    }

    start_power = 5.0f;
    end_power = -3.5f;
    range = end_power - start_power;
    step = range / (N_power -1);

    for(int32_t i = 0; i < N_power; i++){
        float x = start_power + i * step;
        q_t a = float_to_q(x);
        q_t b = q_int_power(a, -i);

        CU_ASSERT_DOUBLE_EQUAL(pow(x, -i), q_to_float(b), 0.001);
    }

    q_t a = INT_TO_Q(2);
    q_t b = q_int_power(a, 0);
    CU_ASSERT_EQUAL(Q_TO_INT(b), 1);

    a = INT_TO_Q(-5);
    b = q_int_power(a, 3);
    CU_ASSERT_EQUAL(Q_TO_INT(b), -125);

    a = INT_TO_Q(-125);
    b = q_int_power(a, -3);
    CU_ASSERT_DOUBLE_EQUAL(-5.12e-7, q_to_float(b), 0.001);

    a = float_to_q(0.01f);
    b = q_int_power(a, -2);

    CU_ASSERT_DOUBLE_EQUAL(10000.0, q_to_float(b), 10000.0 * 0.01);

    a = float_to_q(0.021);
    b = q_int_power(a, -2);

    CU_ASSERT_DOUBLE_EQUAL(2267.5736961451244, q_to_float(b), 2267.5736961451244 * 0.01);

}

// MARK: - Square Root Q format
const float start_sqrt = 0;
const float end_sqrt = 10000;
const uint16_t N_sqrt = 1 << 12;

void test_q_sqrt()
{
    float range = end_sqrt - start_sqrt;
    float step = range / (N_sqrt - 1);

    for (uint32_t i = 0; i < N_sqrt; i++){
        float x = start_sqrt + i * step;
        q_t a = float_to_q(x);
        q_t b = q_sqrt(a);

        CU_ASSERT_DOUBLE_EQUAL(sqrt(x), q_to_float(b), 0.001);
    }

}

// MARK: Test Trigonometric Functions
const float start_angle  = - 3 * 3.14159265358979323846; // -3 * pi
const float end_angle    = 3 * 3.14159265358979323846;   //  3 * pi
const uint16_t N_trig = 1 << 12; // Number of points to test

// MARK: - Sine Q format
void test_q_sin(){

    float range = end_angle - start_angle;
    float step = range / (N_trig - 1);

    for (uint32_t i = 0; i < N_trig; i++){
        float angle = start_angle + i * step;
        q_t a = float_to_q(angle);
        q_t b = q_sin(a);

        CU_ASSERT_DOUBLE_EQUAL(sin(angle), q_to_float(b), 0.005);
    }

}

// MARK: - Cosine Q format
void test_q_cos(){

    float range = end_angle - start_angle;
    float step = range / (N_trig - 1);

    for (uint32_t i = 0; i < N_trig; i++){
        float angle = start_angle + i * step;
        q_t a = float_to_q(angle);
        q_t b = q_cos(a);

        CU_ASSERT_DOUBLE_EQUAL(cos(angle), q_to_float(b), 0.005);
    }

}

// MARK: - Tangent Q format
void test_q_tan(){

    float range = end_angle - start_angle;
    float step = range / (11 - 1);

    for (uint32_t i = 0; i < 11; i++){
        float angle = start_angle + i * step;
        q_t a = float_to_q(angle);
        q_t b = q_tan(a);
        CU_ASSERT_DOUBLE_EQUAL(tan(angle), q_to_float(b), 0.05); // 0.05 is the maximum error but it goes higher when the angle is close to pi/2 or -pi/2
    }

}

// MARK: - Test Suite
// Test suite initialization
int initialize_suite() {
    return 0;
}

// Test suite cleanup
int cleanup_suite() {
    return 0;
}

// Main function
int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("Q_Format", initialize_suite, cleanup_suite);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite general_math = CU_add_suite("general_math", initialize_suite, cleanup_suite);
    if (NULL == general_math) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite trigonometric = CU_add_suite("trigonometric", initialize_suite, cleanup_suite);
    if (NULL == trigonometric) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // Add the test case to the suite

    /*Q conversion tests*/
    if (NULL == CU_add_test(suite, "Integer_Q_Conversion", testIntToQ)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "Float_Q_Conversion", testFloatToQ)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*Q math tests*/
    if (NULL == CU_add_test(general_math, "Q_Product", testProduct)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(general_math, "Q_Division", testDivision)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(general_math, "Q_Absolute", testAbsolute)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(general_math, "Q_Int_Power", testIntPower)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(general_math, "Q_Sqrt", test_q_sqrt)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*Trigonometric functions tests*/
    if (NULL == CU_add_test(trigonometric, "Q_Sin", test_q_sin)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(trigonometric, "Q_Cos", test_q_cos)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(trigonometric, "Q_Tan", test_q_tan)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
