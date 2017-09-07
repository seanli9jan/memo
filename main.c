#include "cclib.h"
#include "data.h"

#define STR  "Array :"
#define ROWS 5
#define COLS 4
#define CH   3

static bool init(data_t *data, bool flag)
{
    data->flag = flag;
    data->str  = STR;

    switch((uint8_t)data->flag) {
        case 0: 
            data->shape.rows = ROWS;
            data->shape.cols = COLS;
            data->shape.ch   = CH;

            data->ary = (float *)malloc(data->shape.rows * \
                                        data->shape.cols * \
                                        data->shape.ch   * \
                                        sizeof(float));
            break;

        case 1:
            data->shape.rows = (uint8_t)*((float *)tool_data_o + 0);
            data->shape.cols = (uint8_t)*((float *)tool_data_o + 1);
            data->shape.ch   = (uint8_t)*((float *)tool_data_o + 2);

            data->ary = (float *)tool_data_o + 3;
            break;

        default:
            break;
    }

    return true;
}

static bool release(data_t *data)
{
    free(data->ary);
    return true;
}

void main(void)
{
    data_t data;
    bool flag = true;

    if(init(&data, flag >> 1))
        func(&data);

    if(release(&data))
        data.ary = NULL;

    if(init(&data, flag >> 0))
        func(&data);
}
