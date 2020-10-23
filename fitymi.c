/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetic
 */

// My headers
#include "fitymi.h"

// Standard headers
#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    const double scalingFactor = getScalingFactor(5, 10);
    printf("Time scale: %f\n", scalingFactor);
    return 0;
}

double getScalingFactor(int nodes, int seconds)
{
    double scalingFactor, x, y;
    x = TIME_START/seconds;
    y = 1.0/(nodes - 1.0);
    scalingFactor = 1.0/(pow(x, y));

    return scalingFactor;
}