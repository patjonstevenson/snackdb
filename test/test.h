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

#define TEST(NAME) \
    TestResult #NAME() { \
        TestResult RESULT_OF_TEST_M; \
        RESULT_OF_TEST_M.num_assertions = 0;\
        RESULT_OF_TEST_M.assertions = (*Assertion)malloc(0);


#define END_TEST \
    return RESULT_OF_TEST_M;\
    }

// Need to copy existing assertions into a temporary array\
    // based on the existing num_assertions\
    // or could just copy the address\
    // Then increment num_assertions by 1, create the assertion,\
    // malloc new one with new\
    // num_assertions, loop over temp assertion array, adding\
    // them to the new assertion array\
    // then free the old pointer\
    // then add the new assertion to the last position in the assertion array\

// TODO: Need to come up with a way to create a unique assertion name. Maybe scope this in a function within the macro. Can I use # to declare a name?
#define ASSERT_EQ(EXPR1, EXPR2) \
    do { \
    \
    Assertion* TEMP_ASSERTIONS = &RESULT_OF_TEST_M.assertions;\
    RESULT_OF_TEST_M.assertions = (Assertion*)malloc(sizeof(Assertion) * ++RESULT_OF_TEST_M.num_assertions);\
    for (int ASSERTION_INDEX_M = 0; ASSERTION_INDEX_M < RESULT_OF_TEST_M - 1; ASSERTION_INDEX_M++) {\
        RESULT_OF_TEST_M.assertions[i] = TEMP_ASSERTIONS[i];\
    }\
    Assertion ASSERTION_M; \
    ASSERTION_M.pass_or_fail = (int)(EXPR1 == EXPR2);\
    ASSERTION_M.expected = #EXPR1;\
    ASSERTION_M.actual = #EXPR2;\
    RESULT_OF_TEST_M.assertions[RESULT_OF_TEST_M.num_assertions - 1] = ASSERTION_M;\
    free(TEMP_ASSERTIONS);\
    } while(0);

#endif
