#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef BOOL_LIB
#include <stdbool.h>
#else
typedef enum {false, true} bool;
#endif

typedef struct {
    uint8_t rows;
    uint8_t cols;
    uint8_t ch;
} shape_t;

typedef struct {
    bool  flag;
    char  *str;
    float *ary;
    shape_t shape;
} data_t;

void func(data_t *data);
