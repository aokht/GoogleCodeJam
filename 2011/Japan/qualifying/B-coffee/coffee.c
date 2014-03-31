#include <stdio.h>
#include <stdlib.h>

#define __DEBUG__ 0

typedef long** t_header;
typedef long*  t_headerRow;
typedef long   t_headerElm;
typedef long** t_data;
typedef long*  t_dataRow;
typedef long   t_dataElm;
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
    (*params)->header[0] = (t_headerRow)malloc(sizeof(t_headerElm) * 2);
}

void prepare(p_testcase* params) {
    long i;
    long n;

    scanf("%ld %ld", &(*params)->header[0][0], &(*params)->header[0][1]);

    n = (*params)->header[0][0];

    (*params)->data = (t_data)malloc(sizeof(t_dataRow) * n);
    for (i=0; i<n; i++) {
        (*params)->data[i] = (t_dataRow)malloc(sizeof(t_dataElm) * 3);
        scanf("%ld %ld %ld", &(*params)->data[i][0], &(*params)->data[i][1], &(*params)->data[i][2]);
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

#define COL_C 0
#define COL_T 1
#define COL_S 2

typedef struct {
    long s;
    long t;
    long c;
    long i;
} t_tmpdata;

#define exists(line) line[COL_C] > 0
#define drinkable(line, day) line[COL_T] >= day
#define better(arr, tmp) (tmp.s < arr[COL_S] || (tmp.s == arr[COL_S] && tmp.s < arr[COL_T]))

#define init(tmp)   \
    tmp.s = -1;     \
    tmp.t = -1;     \
    tmp.i = -1;

#define cand(tmp, data, i)  \
    tmp.s = data[i][COL_S]; \
    tmp.t = data[i][COL_T]; \
    tmp.c = data[i][COL_C]; \
    tmp.i = i;

#define drink(data, target, sum) \
    sum += target.s;             \
    data[target.i][COL_C]--;

#define swap(a, b) \
    long* tmp = a; \
    a = b;         \
    b = tmp

void printtmp(t_tmpdata tmp) {
    if (__DEBUG__) {
        printf("s: %ld, t: %ld, c: %ld, i: %ld\n", tmp.s, tmp.t, tmp.c, tmp.i);
    }
}

long findNextDay(t_data data, long n, long day) {
    long i;
    long next = 0;

    for (i=0; i<n; i++) {
        if (next < data[i][COL_T] && data[i][COL_T] < day) {
            next = data[i][COL_T];
        }
    }

    return next;
}

void perform(int x, p_testcase params) {
    long d, next;
    long i, j;
    t_tmpdata tmp;
    long skip, skip_limit;

    long n = params->header[0][0];
    long k = params->header[0][1];
    t_data data = params->data;

    long sum = 0;

    // sort
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if (j != n - 1 && (data[j][COL_T] < data[j+1][COL_T] || (data[j][COL_T] == data[j+1][COL_T] && data[j][COL_S] < data[j+1][COL_S]))) {
                swap(data[j], data[j+1]);
            }
        }
    }

    for (d=data[0][COL_T]; d>0; d--) {
        if (__DEBUG__) {
            printf("%ld / %ld\n", d, k);
        }

        init(tmp);
        for (i=0; i<n; i++) {
            if (exists(data[i]) && drinkable(data[i], d) && better(data[i], tmp)) {
                cand(tmp, data, i);
            }
        }
        printtmp(tmp);

        if (tmp.i != -1) {
            drink(data, tmp, sum);

            next = findNextDay(data, n, d);

            skip_limit = d - next - 1;
            if (data[tmp.i][COL_C] >= skip_limit) {
                skip = skip_limit;
            } else {
                skip = data[tmp.i][COL_C];
            }

            sum += data[tmp.i][COL_S] * skip;
            data[tmp.i][COL_C] -= skip;
            d -= skip;
        } else {
            next = findNextDay(data, n, d);

            skip = d - next - 1;
            d -= skip;
        }
    }

    printf("Case #%d: %ld\n", x, sum);
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
