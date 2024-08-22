#include "test_q_conversion.h"

// MARK: - Integer to Q format
const uint32_t start_N = -1000;
const uint32_t end_N = 1000;
void testInt_Q() {
    uint32_t N = end_N - start_N;
    for (uint32_t i = 0; i < N; i++){
        int32_t x = start_N + i;
        q_t q_x = INT_TO_Q(x);
        CU_ASSERT_EQUAL(Q_TO_INT(q_x), x);
    }

}

// MARK: - Float to Q format
const float start_float = -1000.0;
const float end_float = 1000.0;
const uint16_t N_float = 1 << 12;

void testFloat_Q() {
    float range = end_float - start_float;
    float step = range / (N_float - 1);

    for (uint32_t i = 0; i < N_float; i++){
        float x = start_float + i * step;
        q_t q_x = float_to_q(x);
        CU_ASSERT_DOUBLE_EQUAL(x, q_to_float(q_x), 0.001);
    }

}

// MARK: - Add Tests to Suite
void add_conversion_tests(CU_pSuite suite)
{
    if (NULL == suite) {
        return;
    }

    if (NULL == CU_add_test(suite, "Int_Q_Conversion", testInt_Q)) {
        return;
    }

    if (NULL == CU_add_test(suite, "Float_Q_Conversion", testFloat_Q)) {
        return;
    }
}
