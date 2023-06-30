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

#endif
