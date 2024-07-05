#include <stdio.h>
#include <CUnit/Basic.h>
#include "../include/fix_point.h"

// Test case
void testIntToQ() {
    CU_ASSERT_EQUAL(Q_FORMAT, Q_FORMAT_CUSTOM);
    int32_t x = 1;
    q_t q_x = INT_TO_Q(x);
    CU_ASSERT_EQUAL(Q_ONE, q_x);

    x = 0;
    q_x = INT_TO_Q(x);
    CU_ASSERT_EQUAL(Q_ZERO, q_x);
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

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
