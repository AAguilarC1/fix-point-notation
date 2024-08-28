#include "test_q_matrix.h"
//TODO: Implement tests for q_matrix.c

void test_q_matrix_alloc()
{
    for (size_t i = 1; i < 100; i++)
    {
        for(size_t j = 1; j < 100; j++)
        {
            // Allocate the matrix
            q_matrix_t m = q_matrix_alloc(i, j);
            CU_ASSERT_PTR_NOT_NULL(m.elements); // Check if the matrix was allocated
            CU_ASSERT_EQUAL(m.rows, i); // Check if the number of rows is correct
            CU_ASSERT_EQUAL(m.cols, j); // Check if the number of columns is correct

            // Free the matrix
            q_matrix_free(&m);
            CU_ASSERT_PTR_NULL(m.elements); // Check if the matrix was freed
        }
    }

    // test slice row and column
    for(size_t i = 1; i < 20; i++)
    {
        for(size_t j = 1; j < 20; j++)
        {
            q_matrix_t m = q_matrix_alloc(i, j);

            // Fill the matrix
            q_matrix_fill_float(&m, 1.0f * i);

            // Slice the matrix
            for(size_t k = 0; k < i; k++)
            {
                q_matrix_t dst = q_matrix_alloc(1, j);
                q_matrix_slice_row(&m, &dst, k);

                // Check if the matrix was sliced correctly
                for(size_t l = 0; l < j; l++)
                {
                    CU_ASSERT_EQUAL(Q_MATRIX_AT(&dst, 0, l), Q_MATRIX_AT(&m, k, l));
                }

                q_matrix_free(&dst);
            }

            // slice column
            for(size_t k = 0; k < j; k++)
            {
                q_matrix_t dst = q_matrix_alloc(i, 1);
                q_matrix_slice_col(&m, &dst, k);

                // Check if the matrix was sliced correctly
                for(size_t l = 0; l < i; l++)
                {
                    CU_ASSERT_EQUAL(Q_MATRIX_AT(&dst, l, 0), Q_MATRIX_AT(&m, l, k));
                }

                q_matrix_free(&dst);
            }

            q_matrix_free(&m);
        }
    }

    // test submatrix
    for(size_t i = 3; i < 20; i++)
    {
        for(size_t j = 3; j < 20; j++)
        {
            q_matrix_t m = q_matrix_alloc(i, j);

            // Fill the matrix
            q_matrix_fill_float(&m, 1.0f * i);

            // Slice the matrix
            for(size_t k = 0; k < i; k++)
            {
                for(size_t l = 0; l < j; l++)
                {
                    q_matrix_t dst = q_matrix_alloc(i - 1, j - 1);
                    q_matrix_submatrix(&m, &dst, k, l);

                    // Check if the matrix was sliced correctly
                    size_t n = 0;
                    for(size_t o = 0; o < i; o++)
                    {
                        if (o == k)
                        {
                            continue;
                        }

                        size_t t = 0;
                        for(size_t p = 0; p < j; p++)
                        {
                            if (p == l)
                            {
                                continue;
                            }
                            // Check if the matrix was sliced correctly
                            CU_ASSERT_EQUAL(Q_MATRIX_AT(&dst, n, t), Q_MATRIX_AT(&m, o, p));
                            t++;
                        }
                        n++;
                    }

                    q_matrix_free(&dst);
                }
            }
            // Free the matrix
            q_matrix_free(&m);
        }
    }

}

void test_q_fill()
{
    for (size_t i = 1; i < 20; i++)
    {
        for(size_t j = 1; j < 20; j++)
        {
            // Allocate the matrix
            q_matrix_t m = q_matrix_alloc(i, j);
            q_t value = float_to_q((float) i * j);

            // Fill the matrix
            q_matrix_fill(&m, value);

            // Check if the matrix was filled correctly
            for (size_t k = 0; k < i; k++)
            {
                for (size_t l = 0; l < j; l++)
                {
                    CU_ASSERT_EQUAL(Q_MATRIX_AT(&m, k, l), value);
                }
            }
            // Free the matrix
            q_matrix_free(&m);
        }
    }

    // Test the fill with random values
    q_t Q_MIN = INT_TO_Q(-100);
    q_t Q_MAX = INT_TO_Q(100);

    for (size_t i = 1; i < 20; i++)
    {
        for(size_t j = 1; j < 20; j++)
        {
            // Allocate the matrix
            q_matrix_t m = q_matrix_alloc(i, j);

            // Fill the matrix with random values
            q_matrix_fill_rand(&m, Q_MIN, Q_MAX);

            // Check if the matrix was filled correctly
            for (size_t k = 0; k < i; k++)
            {
                for (size_t l = 0; l < j; l++)
                {
                    CU_ASSERT_TRUE(Q_MATRIX_AT(&m, k, l) >= Q_MIN);
                    CU_ASSERT_TRUE(Q_MATRIX_AT(&m, k, l) <= Q_MAX);
                }
            }
            // Free the matrix
            q_matrix_free(&m);
        }
    }

    // Test identity matrix
    for (size_t i = 1; i < 20; i++)
    {
        // Allocate the matrix
        q_matrix_t m = q_matrix_alloc(i, i);

        // Fill the matrix with the identity matrix
        q_matrix_identity(&m);

        // Check if the matrix was filled correctly
        for (size_t k = 0; k < i; k++)
        {
            for (size_t l = 0; l < i; l++)
            {
                if (k == l)
                {
                    CU_ASSERT_EQUAL(Q_MATRIX_AT(&m, k, l), Q_ONE);
                }
                else
                {
                    CU_ASSERT_EQUAL(Q_MATRIX_AT(&m, k, l), Q_ZERO);
                }
            }
        }
        // Free the matrix
        q_matrix_free(&m);
    }

}

void add_matrix_tests(CU_pSuite suite)
{
    if (NULL == suite) {
        return;
    }

    if(NULL == CU_add_test(suite, "test_q_matrix_alloc", test_q_matrix_alloc)) {
        return;
    }

    if(NULL == CU_add_test(suite, "test_q_fill", test_q_fill)) {
        return;
    }

}
