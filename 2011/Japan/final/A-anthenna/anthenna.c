#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

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
    long i;
    long n;

    scanf("%lld", &(*params)->header[0][0]);

    n = (*params)->header[0][0];

    (*params)->data = (t_data)malloc(sizeof(t_dataRow));
    (*params)->data[0] = (t_dataRow)malloc(sizeof(t_dataElm) * n);
    for (i=0; i<n; i++) {
        scanf("%lld", &(*params)->data[0][i]);
    }
}

void release(p_testcase params) {
    long i;
    long num = sizeof(params->data) / sizeof(t_dataRow);

    for (i=0; i<num; i++) {
        free(params->data[i]);
    }
    free(params->data);
}

void teardown(p_testcase params) {
    free(params->header[0]);
    free(params->header);
    free(params);
}

#define swap(a, b)    \
    int64_t tmp = a;  \
    a = b;            \
    b = tmp

void perform(int x, p_testcase params) {
    long i, j;

    long n = params->header[0][0];
    t_dataRow data_raw = params->data[0];
    t_dataElm data[n];

    double sint = fabs(sin(2.0 * M_PI / n));
    double p = 0;

    // sort
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if (j != n - 1 && (data_raw[j] < data_raw[j+1])) {
                swap(data_raw[j], data_raw[j+1]);
            }
        }
    }

    i = 0;
    for (j=n-1; j>=0; j=j-2) {
        data[i++] = data_raw[j];
    }
    for (j=(n%2)?1:0; j<n; j=j+2) {
        data[i++] = data_raw[j];
    }

    for (i=0; i<n; i++) {
        p += data[i%n] * data[(i+1)%n] * sint / 2.0;
    }

    printf("Case #%d: %f\n", x, p);
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
