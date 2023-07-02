#ifndef RUN_TEST_H
#define RUN_TEST_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct {
    int pass_or_fail;
    char* name;
    char* expected;
    char* actual;
} Assertion;

typedef struct {
    int num_assertions;
    Assertion* assertions;
} TestResult;

typedef TestResult(*Test)();

// TODO: Instead of va_list, just pass an array of function pointers.
int run_tests(int num_tests, ...) {
    va_list tests;

    va_start(tests, num_tests);

    int num_tests_remaining = num_tests;

    int successes = 0;

    int num_failed_tests = 0;
    while (num_tests_remaining > 0) {
        Test test = va_arg(tests, Test);
        TestResult result = (*test)();

        for (int i = 0; i < result.num_assertions; i++) {
            Assertion assertion = result.assertions[i];
        
            if (1 != assertion.pass_or_fail) {
                num_failed_tests += 1;
                printf("Failure: %s\n", assertion.name);
                printf("Expected: %s\n", assertion.expected);
                printf("Actual: %s\n", assertion.actual);
            }
        }
        free(result.assertions);
        num_tests_remaining--;
    }
    successes = num_tests - num_failed_tests;

    printf("%d/%d tests passed\n", successes, num_tests);

    return successes;
}

TestResult test_one() {
    TestResult result;
    result.num_assertions = 1;
    Assertion assertion;
    assertion.pass_or_fail = 0;
    assertion.name = "test_one";
    assertion.expected = "foo";
    assertion.actual = "bar";
    result.assertions = (Assertion*)malloc(result.num_assertions * sizeof(Assertion));
    result.assertions[0] = assertion;

    return result;
}


#define CONCAT(EXPR1, EXPR2) EXPR1##EXPR2

#define RESIZE_ARRAY(ARRAY_ADDRESS, CURRENT_ARRAY_LENGTH_ADDRESS, ARRAY_ELEMENT_TYPE) \
    Assertion* TEMP_ASSERTIONS = ARRAY_ADDRESS; \
    ARRAY_ADDRESS = (ARRAY_ELEMENT_TYPE*)malloc(sizeof(ARRAY_ELEMENT_TYPE) * ++(*CURRENT_ARRAY_LENGTH_ADDRESS)); \
    \
    for (int ASSERTION_INDEX_M = 0; ASSERTION_INDEX_M < RESULT_OF_TEST_M - 1; ASSERTION_INDEX_M++) { \
        ARRAY_ADDRESS[i] = TEMP_ASSERTIONS[i]; \
    } \

#define TEST_ARRAY_NAME() CONCAT("TEST_", __FILE__)

#define TEST_COUNT_NAME() CONCAT("TEST_COUNT_", __FILE__)

// Declares array of name TEST_<file_path> and test count TEST_COUNT_<file_path> to be imported by test main for use in run_tests
#define TEST_FILE_START \
    Test* TEST_ARRAY_NAME(); \
    int TEST_COUNT_NAME() = 0; \
    char* MOST_RECENT_TEST_NAME = "";

#define VSTR(EXPR) #EXPR

#define STR(EXPR) VSTR(EXPR)


// Begin test function.
#define TEST(TEST_NAME) \
    /* Need to make space for the new test in tests array and increment the test count. */ \
    RESIZE_ARRAY(TEST_ARRAY_NAME(), &TEST_COUNT_NAME(), Test); \
    \
    /* Need to undef and redef most recent test name so we can add it to test array in END_TEST */\
    /*#undef MOST_RECENT_TEST_NAME */ \
    /*#define most_recent_test_name str(name)*/ \
    MOST_RECENT_TEST_NAME = str(name) \
    \
    /* Now we can create our new test */ \
    TestResult TEST_NAME() { \
    TestResult RESULT_OF_TEST_M; \
    RESULT_OF_TEST_M.num_assertions = 0;\
    RESULT_OF_TEST_M.assertions = (*Assertion)malloc(0);\

// Close out test function
#define END_TEST \
    return RESULT_OF_TEST_M;\
    }

#define ASSERT_EQ(EXPR1, EXPR2) \
    do { \
        RESIZE_ARRAY(&RESULT_OF_TEST_M.assertions, &RESULT_OF_TEST_M.num_assertions, ASSERTION) \
        \
        Assertion ASSERTION_M; \
        ASSERTION_M.pass_or_fail = (int)(EXPR1 == EXPR2); \
        ASSERTION_M.expected = #EXPR1; \
        ASSERTION_M.actual = #EXPR2; \
        RESULT_OF_TEST_M.assertions[RESULT_OF_TEST_M.num_assertions - 1] = ASSERTION_M; \
        \
        free(TEMP_ASSERTIONS); \
    } while(0);
#endif
