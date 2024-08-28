#include "test.h"

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
    CU_pSuite conversions = CU_add_suite("Q_Format", initialize_suite, cleanup_suite);
    if (NULL == conversions) {
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
    
    CU_pSuite matrix = CU_add_suite("matrix", initialize_suite, cleanup_suite);

    // Add the test cases to the suite
    add_conversion_tests(conversions);
    add_general_math_tests(general_math);
    add_trigonometric_tests(trigonometric);
    add_matrix_tests(matrix);

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
