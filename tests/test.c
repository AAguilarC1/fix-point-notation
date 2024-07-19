#include <stdio.h>
#include <CUnit/Basic.h>
#include "../include/fix_point.h"

uint8_t approx_equal(float a, float b, float epsilon) {
    if (b > a) {
        return (b - a) < epsilon;
    }
    return (a - b) < epsilon;
}

// Test case
// MARK: - Integer to Q format
void testIntToQ() {
    CU_ASSERT_EQUAL(Q_FORMAT, Q_FORMAT_CUSTOM);
    int32_t x1 = 1;
    q_t q_x = INT_TO_Q(x1);
    CU_ASSERT_EQUAL(Q_ONE, q_x);

    int32_t x2 = 0;
    q_x = INT_TO_Q(x2);
    CU_ASSERT_EQUAL(Q_ZERO, q_x);

    int32_t x3 = -1;
    q_x = INT_TO_Q(x3);
    CU_ASSERT_EQUAL(Q_MINUS_ONE, q_x);

    int32_t x4 = 70;
    q_x = INT_TO_Q(x4);
    CU_ASSERT_EQUAL(Q_TO_INT(q_x), 70);

    int32_t x5 = -70;
    q_x = INT_TO_Q(x5);
    CU_ASSERT_EQUAL(Q_TO_INT(q_x), -70);
}

// MARK: - Float to Q format
void testFloatToQ() {
    float x = 0.5;
    q_t q_x = float_to_q(x);
    CU_ASSERT_EQUAL(approx_equal(x, q_to_float(q_x), 0.001), 1);

    x = 0.25;
    q_x = float_to_q(x);
    CU_ASSERT_EQUAL(approx_equal(x, q_to_float(q_x), 0.001), 1);

    x = 0.1234;
    q_x = float_to_q(x);
    CU_ASSERT_EQUAL(approx_equal(x, q_to_float(q_x), 0.001), 1);

    x = 0.0;
    q_x = float_to_q(x);
    CU_ASSERT_EQUAL(approx_equal(x, q_to_float(q_x), 0.001), 1);

    x = 0.0000001;
    q_x = float_to_q(x);
    CU_ASSERT_EQUAL(approx_equal(x, q_to_float(q_x), 0.001), 1);

    q_x = float_to_q(1.0);
    CU_ASSERT_EQUAL(approx_equal(1.0, q_to_float(q_x), 0.001), 1);

    q_x = float_to_q(-1.0);
    CU_ASSERT_EQUAL(approx_equal(-1.0, q_to_float(q_x), 0.001), 1);

    q_x = float_to_q(0.0);
    CU_ASSERT_EQUAL(approx_equal(0.0, q_to_float(q_x), 0.001), 1);

}

void testProduct() {
    q_t a = INT_TO_Q(1);
    q_t b = INT_TO_Q(2);
    q_t c = q_product(a, b);

    CU_ASSERT_EQUAL(Q_TO_INT(c), 2);

    a = INT_TO_Q(2);
    b = INT_TO_Q(2);

    c = q_product(a, b);
    CU_ASSERT_EQUAL(Q_TO_INT(c), 4);

    float x = 0.5;
    a = float_to_q(x);
    b = INT_TO_Q(2);
    c = q_product(a, b);

    CU_ASSERT_EQUAL(approx_equal(x * 2, q_to_float(c), 0.001), 1);

    float y = 0.25;
    a = float_to_q(y);
    x = 0.5;
    b = float_to_q(x);
    c = q_product(a, b);
    
    CU_ASSERT_EQUAL(approx_equal(y * x, q_to_float(c), 0.001), 1);

    float z = 0.0001234;
    y = 0.25;
    x = 0.5;

    a = float_to_q(z);
    b = INT_TO_Q(2);
    c = q_product(a, b);
    
    a = float_to_q(y);
    c = q_product(a, c);
    
    b = float_to_q(x);
    c = q_product(b, c);

    CU_ASSERT_EQUAL(approx_equal(z * 2 * 0.25 * 0.5, q_to_float(c), 0.001), 1);
}

void testDivision(){
    float x = 0.5;
    q_t a = float_to_q(x);
    q_t b = INT_TO_Q(2);

    q_t c = q_division(b, a);
    CU_ASSERT_EQUAL(approx_equal(2 / x, q_to_float(c), 0.001), 1);
    
    c = q_division(a, b);
    CU_ASSERT_EQUAL(approx_equal(x / 2, q_to_float(c), 0.001), 1);

    float y = 0.25;
    x = 0.5;
    a = float_to_q(y);
    b = float_to_q(x);

    c = q_division(a, b);
    CU_ASSERT_EQUAL(approx_equal(y / x, q_to_float(c), 0.001), 1);

    float z = 0.0001234;
    y = 0.25;
    x = 0.5;

    a = float_to_q(z);
    b = float_to_q(y);
    c = q_division(a, b);

    a = float_to_q(x);
    c = q_division(c, a);

    CU_ASSERT_EQUAL(approx_equal((z / y) / x, q_to_float(c), 0.001), 1);

    a = INT_TO_Q(10000);
    b = INT_TO_Q(100);
    c = q_division(a, b);
    CU_ASSERT_EQUAL(Q_TO_INT(c), 100);

    a = INT_TO_Q(1);
    b = INT_TO_Q(1000);
    c = q_division(a, b);
    CU_ASSERT_EQUAL(approx_equal(1 / (1000.0f), q_to_float(c), 0.001), 1);

    x = 0.5;
    a = float_to_q(x);
    b = INT_TO_Q(200);

    c = q_division(a, b);

    CU_ASSERT_EQUAL(approx_equal(x / 200.0f, q_to_float(c), 0.001), 1);

}
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

    // Add the test case to the suite
    if (NULL == CU_add_test(suite, "Int2Q", testIntToQ)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "Float2Q", testFloatToQ)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "Q_Product", testProduct)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "Q_Division", testDivision)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
