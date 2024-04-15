#include <stdio.h>
#include <time.h>
#include "hal.h"


void main(void)
{
    hal_setup(CLOCK_BENCHMARK);

    printf("Hello!!\n");

    unsigned long long cycles_tot=0, cycles1, cycles2;
    double time_taken=0, start, end;

    for (int i = 0; i < N_ITERATIONS; ++i) {

        start = (double) clock();
        cycles1 = PLATFORM_CLOCK();
        // test code here
        cycles2 = PLATFORM_CLOCK();
        end = (double)clock();

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