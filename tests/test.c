#include <stdio.h>
#include <CUnit/Basic.h>
#define Q_FORMAT_CUSTOM 16
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

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
