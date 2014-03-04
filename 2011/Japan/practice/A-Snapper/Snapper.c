#include <stdio.h>
#include <stdlib.h>

#define __DEBUG__ 0

void setup(int*** params) {
    *params =  (int **)malloc(sizeof(int *) * 1);
}

void prepare(int*** params) {
    int** tmp = *params;

    tmp[0] = (int *)malloc(sizeof(int) * 2);
    scanf("%d %d", &tmp[0][0], &tmp[0][1]);
}

void release(int** params) {
}

void teardown(int** params) {
    free(params[0]);
    free(params);
}

void perform(int no, int** params) {
    int n = params[0][0];
    int k = params[0][1];
    int mask = 1;
    int i;

    for (i=0; i<n; i++) {
        mask *= 2;
    }
    mask -= 1;

    if (__DEBUG__)
        printf("n = %d, k = %d, mask = %d\n", n, k, mask);

    printf("Case #%d: ", no);
    if ((k & mask) == mask)
        printf("ON");
    else
        printf("OFF");
    printf("\n");
}

int main(void) {
    int num_test_cases;
    int** params;
    int i;

    scanf("%d", &num_test_cases);

    setup(&params);

    for (i=1; i<=num_test_cases; i++) {
        prepare(&params);
        perform(i, params);
        release(params);
    }

    teardown(params);

    return 0;
}
