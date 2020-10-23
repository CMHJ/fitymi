/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetics
 */

// My headers
#include "fitymi.h"

// Standard headers
#include <stdio.h>
#include <unistd.h> // For sleep
#include <time.h> // For nanosleep, and timestamping
#include <math.h>

int
main(int argc, char const *argv[])
{
    const double scalingFactor = getScalingFactor(5, 10);
    printf("Time scale: %f\n", scalingFactor);

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    long ts1 = getCurrentTimeStampMilliseconds();
    nanosleep(&ts, NULL);
    long ts2 = getCurrentTimeStampMilliseconds();
    printf("Time passed from sleeping: %ld\n", ts2 - ts1);
    return 0;
}

// FUNCTION DEFINITIONS

long
getCurrentTimeStampMilliseconds()
{
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + lround(_t.tv_nsec/1.0e6);
}

double
getScalingFactor(int nodes, int seconds)
{
    double scalingFactor, x, y;
    x = TIME_START/seconds;
    y = 1.0/(nodes - 1.0);
    scalingFactor = 1.0/(pow(x, y));

    return scalingFactor;
}

// TYPE DEFINITIONS

struct folder
{
    const char folderName;
    struct folder* folderList[10];
    const char* fileList[];
};