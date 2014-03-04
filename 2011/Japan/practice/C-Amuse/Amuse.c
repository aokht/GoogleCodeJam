#include <stdio.h>
#include <stdlib.h>

#define __DEBUG__ 0

void setup(long*** params) {
    *params = (long **)malloc(sizeof(long *) * 2);
    **params = (long *)malloc(sizeof(long) * 3);
}

void prepare(long*** params) {
    long i;
    long n;
    long** tmp = *params;

    scanf("%ld %ld %ld", &tmp[0][0], &tmp[0][1], &tmp[0][2]);

    n = tmp[0][2];

    tmp[1] = (long *)malloc(sizeof(long) * n);
    for (i=0; i<n; i++)
        scanf("%ld", &tmp[1][i]);
}

void release(long** params) {
    free(params[1]);
}

void teardown(long** params) {
    free(params[0]);
    free(params);
}

void perform(long x, long** params) {
    long r = params[0][0];
    long k = params[0][1];
    long n = params[0][2];
    long y = 0;
    long* groups = params[1];

    long i, j;
    long top, index, tmp, sum, count;

    i = r;
    j = top = 0;

    while (i-- > 0) {
        sum = 0;

        while (1) {
            index = j % n;
            tmp = sum + groups[index];

            if (tmp > k) {
                break;
            }

            sum = tmp;
            j++;

            if (j - top == n) {
                break;
            }
        }

        if (__DEBUG__)
            printf("top = %ld, index = %ld, sum = %ld\n", top, index, sum);

        y += sum;
        top = j;

        // input data pattern is looped
        if (top % n == 0) {
            count = r - i;
            y += y * (r / count - 1);
            i = r % count;
        }
    }

    printf("Case #%ld: %ld\n", x, y);
}

int main(void) {
    long num_test_cases;
    long** params;
    long i;
    setvbuf(stdout, (char *)NULL, _IONBF, 0);  // disable buffer

    scanf("%ld", &num_test_cases);

    setup(&params);

    for (i=1; i<=num_test_cases; i++) {
        prepare(&params);
        perform(i, params);
        release(params);
    }

    teardown(params);

    return 0;
}
