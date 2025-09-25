static int tests_run = 0, tests_failed = 0;

#define ASSERT(cond, msg) do { \
    tests_run++; \
    if (!(cond)) { \
        fprintf(stderr, "FAIL at %s:%d: %s\n", __FILE__, __LINE__, msg); \
        tests_failed++; \
    } \
} while(0)

#define RUN_TEST(fn) do { \
    fprintf(stderr, "Running %s...\n", #fn); \
    fn(); \
} while(0)

static void tests_summary() {
    fprintf(stderr, "\n--- Tests run: %d, Failures: %d ---\n", tests_run, tests_failed);
    if (tests_failed == 0) fprintf(stderr, "ALL TESTS PASSED ✅\n");
    else fprintf(stderr, "SOME TESTS FAILED ❌\n");
}


