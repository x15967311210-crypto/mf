/*
 * Host-side unit tests for the Q8.8 fixed-point helpers in src/fixed_point.c.
 *
 * The real engine functions are linked in by the Makefile's host-test target:
 *
 *   cc ... tests/host/fixed_point_test.c src/fixed_point.c -Wl,--gc-sections ...
 *
 * Expectations use the Q_8_8 macros from include/macros.h rather than a copy
 * of the implementation.
 */

#include "test.h"

#include "fixed_point.h"
#include "macros.h"

/* ------------------------------------------------------------------ */
/* FixedMultiplication                                                 */
/* ------------------------------------------------------------------ */

static void test_fixed_multiplication(void)
{
    CHECK_EQ(FixedMultiplication(Q_8_8(1.f), Q_8_8(1.f)), Q_8_8(1.f));
    CHECK_EQ(FixedMultiplication(Q_8_8(1.5f), Q_8_8(0.5f)), Q_8_8(0.75f));
    CHECK_EQ(FixedMultiplication(Q_8_8(0.5f), Q_8_8(0.5f)), Q_8_8(0.25f));
    CHECK_EQ(FixedMultiplication(Q_8_8(2.f), Q_8_8(3.f)), Q_8_8(6.f));

    /* Negative operands keep the sign; exact Q8.8 products. */
    CHECK_EQ(FixedMultiplication(Q_8_8(-1.f), Q_8_8(1.f)), Q_8_8(-1.f));
    CHECK_EQ(FixedMultiplication(Q_8_8(-1.5f), Q_8_8(0.5f)), Q_8_8(-0.75f));
    CHECK_EQ(FixedMultiplication(Q_8_8(-1.5f), Q_8_8(-0.5f)), Q_8_8(0.75f));

    /* Integer division truncates toward zero. */
    CHECK_EQ(FixedMultiplication(0x1, 0x80), 0);
    CHECK_EQ(FixedMultiplication(0x3, 0x80), 1);
    CHECK_EQ(FixedMultiplication(0x1, -0x80), 0);
}

/* ------------------------------------------------------------------ */
/* FixedDivision                                                       */
/* ------------------------------------------------------------------ */

static void test_fixed_division(void)
{
    CHECK_EQ(FixedDivision(Q_8_8(1.f), Q_8_8(1.f)), Q_8_8(1.f));
    CHECK_EQ(FixedDivision(Q_8_8(1.f), Q_8_8(0.5f)), Q_8_8(2.f));
    CHECK_EQ(FixedDivision(Q_8_8(0.5f), Q_8_8(2.f)), Q_8_8(0.25f));
    CHECK_EQ(FixedDivision(Q_8_8(3.f), Q_8_8(2.f)), Q_8_8(1.5f));

    CHECK_EQ(FixedDivision(Q_8_8(-1.f), Q_8_8(1.f)), Q_8_8(-1.f));
    CHECK_EQ(FixedDivision(Q_8_8(1.f), Q_8_8(-0.5f)), Q_8_8(-2.f));
    CHECK_EQ(FixedDivision(Q_8_8(-1.f), Q_8_8(-0.5f)), Q_8_8(2.f));

    /* Truncation toward zero: 0.5 / 3.0 = 42/256. */
    CHECK_EQ(FixedDivision(Q_8_8(0.5f), Q_8_8(3.f)), 42);
}

/* ------------------------------------------------------------------ */
/* FixedInverse                                                        */
/* ------------------------------------------------------------------ */

static void test_fixed_inverse(void)
{
    CHECK_EQ(FixedInverse(Q_8_8(1.f)), Q_8_8(1.f));
    CHECK_EQ(FixedInverse(Q_8_8(0.5f)), Q_8_8(2.f));
    CHECK_EQ(FixedInverse(Q_8_8(2.f)), Q_8_8(0.5f));
    CHECK_EQ(FixedInverse(Q_8_8(0.25f)), Q_8_8(4.f));

    CHECK_EQ(FixedInverse(Q_8_8(-1.f)), Q_8_8(-1.f));
    CHECK_EQ(FixedInverse(Q_8_8(-0.5f)), Q_8_8(-2.f));
    CHECK_EQ(FixedInverse(Q_8_8(-2.f)), Q_8_8(-0.5f));

    /* Truncation toward zero: 1.0 / 3.0 = 85/256. */
    CHECK_EQ(FixedInverse(Q_8_8(3.f)), 85);
    CHECK_TRUE(FixedInverse(Q_8_8(0.5f)) > FixedInverse(Q_8_8(1.f)));
}

int main(void)
{
    test_fixed_multiplication();
    test_fixed_division();
    test_fixed_inverse();

    if (g_host_test_failures != 0)
        return host_test_finish();

    printf("fixed-point-test: %d/%d passed\n",
           g_host_test_checks, g_host_test_checks);
    return 0;
}
