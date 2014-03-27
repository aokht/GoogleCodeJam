#include <stdio.h>
#include <stdlib.h>

#define __DEBUG__ 0

typedef int** t_header;
typedef int*  t_headerRow;
typedef int   t_headerElm;
typedef int** t_data;
typedef int*  t_dataRow;
typedef int   t_dataElm;
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
    (*params)->header[0] = (t_headerRow)malloc(sizeof(t_headerElm) * 3);
}

void prepare(p_testcase* params) {
    int i;
    int c;

    scanf("%d %d %d", &(*params)->header[0][0], &(*params)->header[0][1], &(*params)->header[0][2]);

    c = (*params)->header[0][1];

    (*params)->data = (t_data)malloc(sizeof(t_dataRow) * c);
    for (i=0; i<c; i++) {
        (*params)->data[i] = (t_dataRow)malloc(sizeof(t_dataElm) * 2);
        scanf("%d %d", &(*params)->data[i][0], &(*params)->data[i][1]);
    }
}

void release(p_testcase params) {
    int i;
    int num = sizeof(params->data) / sizeof(t_dataRow);

    for (i=0; i<num; i++) {
        free(params->data[i]);
    }
    free(params->data);
}

void teardown(p_testcase params) {
    free(params->header);
    free(params);
}


void perform(int x, p_testcase params) {
    int a, b;
    int i;

    int m = params->header[0][0];
    int c = params->header[0][1];
    int w = params->header[0][2];

    int position = w;

    for (i=c-1; i>=0; i--) {
        a = params->data[i][0];
        b = params->data[i][1];

        if (position <= b) {
            // move itself
            position = a + position - 1;
        } else if (position <= a + b - 1) {
            // involved
            position = position - b;
        }
    }

    printf("Case #%d: %d\n", x, position);
}

int main(void) {
    int num_test_cases;
    p_testcase params;
    int i;
    setvbuf(stdout, (char *)NULL, _IONBF, 0);  // disable buffer

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
