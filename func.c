#include "cclib.h"

void func(data_t *data)
{
    uint8_t i, j, k;
    float *ptr;

    printf("| %s |\n", data->str);

    for (i = 0; i < data->shape.rows; i++) {
        printf("|");
        for (j = 0; j < data->shape.cols; j++) {
            for (k = 0; k < data->shape.ch; k++) {
                (!data->flag)?
                    (*(data->ary + (i * data->shape.cols + j) * data->shape.ch + k) =     \
                                   (i * data->shape.cols + j) * data->shape.ch + k  +  10):
                    (*(data->ary + (i * data->shape.cols + j) * data->shape.ch + k) += 10);

                ptr = data->ary + (i * data->shape.cols + j) * data->shape.ch + k;
                printf(" %.2f ", *ptr);
            }
            printf("|");
        }
        printf("\n");
    }
}
