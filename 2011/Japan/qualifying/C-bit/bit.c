#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define __DEBUG__ 0

typedef int64_t** t_header;
typedef int64_t*  t_headerRow;
typedef int64_t   t_headerElm;
typedef int64_t** t_data;
typedef int64_t*  t_dataRow;
typedef int64_t   t_dataElm;
typedef t_header* p_header;
typedef t_data*   p_data;

typedef struct {
    t_header header;
    t_data   data;
} t_testcase;

typedef t_testcase* p_testcase;

void setup(p_testcase* params) {
    *params = (p_testcase)malloc(sizeof(t_testcase));
    (*params)->header = (t_header)malloc(sizeof(t_headerRow) * 1);
    (*params)->header[0] = (t_headerRow)malloc(sizeof(t_headerElm) * 1);
}

void prepare(p_testcase* params) {
    scanf("%lld", &(*params)->header[0][0]);
}

void release(p_testcase params) {
}

void teardown(p_testcase params) {
    free(params->header[0]);
    free(params->header);
    free(params);
}

int countBit(int64_t n) {
    int count = 0;

    do { 
        if (n & 1) {
            count++;
        }
    } while (n >>= 1);

    return count;
}

#define llpow2(n) (2LL << ((n) - 1))

void perform(int x, p_testcase params) {
    int64_t n = params->header[0][0];
    int64_t a, b;
    int i, count;
    int max = (n == 0) ? 0 : 1;

    for (i=0; llpow2(i+1) <= n; i++) {
        a = llpow2(i+1) - 1;
        b = n - a;

        count = countBit(a) + countBit(b);
        if (count > max) {
            max = count;
        }
    }

    printf("Case #%d: %d\n", x, max);
}

int main(int argc, char** argv) {
    int num_test_cases;
    p_testcase params;
    int i;
    int case_num = -1;
    setvbuf(stdout, (char *)NULL, _IONBF, 0);  // disable buffer
    
    if (argc == 2) {
        case_num = atoi(argv[1]);
    }

    scanf("%d", &num_test_cases);

    setup(&params);

    for (i=1; i<=num_test_cases; i++) {
        prepare(&params);
        if (case_num == -1 || i == case_num) {
            perform(i, params);
        }
        release(params);
    }

    teardown(params);

    return 0;
}
