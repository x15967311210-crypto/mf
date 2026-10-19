/*
 * Minimal host-side assertion helpers for the mf-hack test harness.
 *
 * These helpers are intentionally dependency-free: no framework, no
 * allocation, no GBA headers.  Each CHECK_* macro reports the source location
 * of the failed assertion and increments the process-wide counters; a test
 * program finishes with host_test_finish().
 */

#ifndef HOST_TEST_H
#define HOST_TEST_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int g_host_test_checks;
static int g_host_test_failures;

static int host_check_true(int condition, const char *expression,
                           const char *file, int line)
{
    g_host_test_checks++;
    if (!condition)
    {
        fprintf(stderr, "%s:%d: CHECK_TRUE failed: %s\n",
                file, line, expression);
        g_host_test_failures++;
        return 0;
    }
    return 1;
}

static int host_check_eq(unsigned long long actual,
                         unsigned long long expected,
                         const char *actual_expr,
                         const char *expected_expr,
                         const char *file, int line)
{
    g_host_test_checks++;
    if (actual != expected)
    {
        fprintf(stderr,
                "%s:%d: CHECK_EQ failed: %s == %s "
                "(actual 0x%llx, expected 0x%llx)\n",
                file, line, actual_expr, expected_expr, actual, expected);
        g_host_test_failures++;
        return 0;
    }
    return 1;
}

static int host_check_memeq(const void *actual, const void *expected,
                            size_t size, const char *actual_expr,
                            const char *expected_expr,
                            const char *file, int line)
{
    const unsigned char *a = (const unsigned char *)actual;
    const unsigned char *e = (const unsigned char *)expected;
    size_t i;

    g_host_test_checks++;
    for (i = 0; i < size; i++)
    {
        if (a[i] != e[i])
        {
            fprintf(stderr,
                    "%s:%d: CHECK_MEMEQ failed: %s[%zu] == %s[%zu] "
                    "(actual 0x%02x, expected 0x%02x)\n",
                    file, line, actual_expr, i, expected_expr, i,
                    a[i], e[i]);
            g_host_test_failures++;
            return 0;
        }
    }
    return 1;
}

#define CHECK_TRUE(condition) \
    host_check_true(!!(condition), #condition, __FILE__, __LINE__)

#define CHECK_EQ(actual, expected) \
    host_check_eq((unsigned long long)(actual), \
                  (unsigned long long)(expected), \
                  #actual, #expected, __FILE__, __LINE__)

#define CHECK_MEMEQ(actual, expected, size) \
    host_check_memeq((actual), (expected), (size), \
                     #actual, #expected, __FILE__, __LINE__)

/* Print the summary and return the process exit status. */
static int host_test_finish(void)
{
    if (g_host_test_failures != 0)
    {
        fprintf(stderr, "host-test: %d/%d passed (%d failed)\n",
                g_host_test_checks - g_host_test_failures,
                g_host_test_checks, g_host_test_failures);
        return 1;
    }

    printf("host-test: %d/%d passed\n",
           g_host_test_checks, g_host_test_checks);
    return 0;
}

#endif /* HOST_TEST_H */
