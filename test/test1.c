#include <assert.h>
#include <stdio.h>

int test1() {
    assert(1==1);
    printf("TEST 1: SUCCESS\n");
    return 0;
}

int main() {
    test1();
    //assert(1 == 2);
    return 0;
}
