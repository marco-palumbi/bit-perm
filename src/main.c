#include <stdio.h>
#include <time.h>
#include "hal.h"

#include <stdint.h>
#include <string.h>

#define BIT_ARRAY_BYTE_SIZE 64
#define PERM_SIZE  (BIT_ARRAY_BYTE_SIZE * 8)

typedef uint8_t bit_array_t[BIT_ARRAY_BYTE_SIZE];
#define ALIAS(bit_m) (uint32_t *)(0x22000000 + ((unsigned)((void *)bit_m - 0x20000000) * 32U))

void main(void)
{
    hal_setup(CLOCK_BENCHMARK);

    printf("Hello!!\n");

    bit_array_t volatile bit_array = {0xff,0x00};
    uint32_t volatile * const array_alias = ALIAS(bit_array);
    uint16_t permutation[PERM_SIZE];

    printf("Alias address %X\n", array_alias);

    // initialize permutation
    for(int j = 0; j < PERM_SIZE; j++) {
        permutation[j] = j;
    }
    permutation[1] = 10;
    permutation[10] = 1;

    unsigned long long cycles_tot=0, cycles1, cycles2;
    double time_taken=0, start, end;

    for (int i = 0; i < N_ITERATIONS; ++i) {

        printf("%0x %0X\n", bit_array[0], bit_array[1]);
        start = (double) clock();
        cycles1 = PLATFORM_CLOCK();
        // apply permutation
        uint32_t buffer[PERM_SIZE];
        for(int j = 0; j < PERM_SIZE; j++) {
            buffer[permutation[j]] = array_alias[j];
        }
        memcpy((uint32_t *)array_alias, buffer, sizeof(buffer));

        cycles2 = PLATFORM_CLOCK();
        end = (double)clock();
        printf("%0x %0X\n", bit_array[0], bit_array[1]);

        time_taken += (end - start) / ((double) CLOCKS_PER_SEC);
        cycles_tot += cycles2 - cycles1;
    }

    // computes measurement overhead
    cycles1 = PLATFORM_CLOCK();
    cycles2 = PLATFORM_CLOCK();

    printf("Iterations %d: %10lld ", N_ITERATIONS, cycles_tot/N_ITERATIONS + cycles1 - cycles2);
    printf("cycles");
    printf("\n");
    printf("Time taken %lf\n\n", time_taken/N_ITERATIONS);

}