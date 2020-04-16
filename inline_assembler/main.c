#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void func(int32_t start, int32_t stop, int32_t step)
{
    int32_t len = stop / step, size = sizeof(int);
    int32_t *list = malloc(size*len);
    int32_t sum, i;
    float sum_f, len_f, mean;

    asm volatile
    (
        "movl %[start], %%eax\n\t"  // %eax = 0
        "movl %[start], %%ebx\n\t"  // %ebx = 0
        "LOOP:"                     // start LOOP 
        "movl %%eax, (%[list])\n\t" // *list = %eax
        "addl $4, %[list]\n\t"      // list += 1
        "addl %%eax, %%ebx\n\t"     // %ebx += %eax
        "addl %[step], %%eax\n\t"   // %eax += step
        "cmpl %%eax, %[stop]\n\t"   // if %eax <= stop:
        "jg LOOP\n\t"               // goto LOOP else BREAK 
        "movl %%ebx, %[sum]\n\t"    // total = %ebx
        : [sum]"=r"(sum)      /* output    operands */
        : [start]"r"(start),  /* input     operands */
          [stop]"r"(stop),    /*                    */
          [step]"r"(step),    /*                    */
          [list]"r"(list)     /*                    */
        : "%eax", "%ebx"      /* clobbered operands */
    );

    sum_f = (float)sum;
    len_f = (float)len;

    asm volatile
    (
        "flds %[sum]\n\t"  // sum.to("fpu")
        "fdivs %[len]\n\t" // sum / len.to("fpu")
        : [mean]"=t"(mean)  /* output    operands */
        : [sum]"m"(sum_f),  /* input     operands */
          [len]"m"(len_f)   /*                    */
        :                   /* clobbered operands */
    );

    for (i = 0; i < len; i++)
        printf(!i ? "[%d" : i == len - 1 ? ", %d]\n" : ", %d", list[i]);
    printf("sum  = %d\n", sum);
    printf("mean = %.1f\n", mean);

    free(list);
}

void main(void)
{
    int32_t start = 0, stop = 10, step = 1;
    func(start, stop, step);
}
