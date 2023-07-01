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

int run_tests(int num_tests, ...) {
    va_list tests;

    va_start(tests, num_tests);

    int num_tests_remaining = num_tests;

    int successes = 0;

    int num_failed_tests = 0;
    while (num_tests_remaining > 0) {
        Test test = va_arg(tests, Test);
        TestResult result = (*test)();
        //int does_test_pass = 0;
        for (int i = 0; i < result.num_assertions; i++) {
            Assertion assertion = result.assertions[i];
            //if (assertion.pass_or_fail) {
            //    does_test_pass += 0;
            //}
        
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


#define CONCAT(EXPR1, EXPR2) EXPR1 ## EXPR2

#define RESIZE_ARRAY(ARRAY_ADDRESS, CURRENT_ARRAY_LENGTH_ADDRESS, ARRAY_ELEMENT_TYPE) \
    Assertion* TEMP_ASSERTIONS = ARRAY_ADDRESS; /*&RESULT_OF_TEST_M.assertions;*/ \
    ARRAY_ADDRESS = (ARRAY_ELEMENT_TYPE*)malloc(sizeof(ARRAY_ELEMENT_TYPE) * ++(*CURRENT_ARRAY_LENGTH_ADDRESS)); \
    \
    for (int ASSERTION_INDEX_M = 0; ASSERTION_INDEX_M < RESULT_OF_TEST_M - 1; ASSERTION_INDEX_M++) { \
        ARRAY_ADDRESS[i] = TEMP_ASSERTIONS[i]; \
    } \

#define TEST_FILE_NAME() CONCAT("TEST_", __FILE__)

#define TEST_FILE \
    Test* TEST_FILE_NAME()

// Begin test function.
#define TEST(NAME) \
    /* Need to add the new test to tests array. */ \
    TEST_FILE_NAME() \
    \
    /* Now we can create our new test */ \
    TestResult #NAME() { \
        TestResult RESULT_OF_TEST_M; \
        RESULT_OF_TEST_M.num_assertions = 0;\
        RESULT_OF_TEST_M.assertions = (*Assertion)malloc(0);

// Close out test function
#define END_TEST \
    return RESULT_OF_TEST_M;\
    }

/*
  Need to resize our assertions array  \
        Assertion* TEMP_ASSERTIONS = &RESULT_OF_TEST_M.assertions; \
        RESULT_OF_TEST_M.assertions = (Assertion*)malloc(sizeof(Assertion) * ++RESULT_OF_TEST_M.num_assertions); \
        \
        for (int ASSERTION_INDEX_M = 0; ASSERTION_INDEX_M < RESULT_OF_TEST_M - 1; ASSERTION_INDEX_M++) { \
            RESULT_OF_TEST_M.assertions[i] = TEMP_ASSERTIONS[i]; \
        } \
        \
 */

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
