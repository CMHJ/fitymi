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
#include <string.h> // For strcpy
#include <ctype.h> // For tolower

int
main(int argc, char const *argv[])
{
    const long buildTime = 5 * 1000;
    const long startTime = getCurrentTimeStampMilliseconds();
    // double timeScalingFactor = getScalingFactor(1, buildTime);
    printf("Start time: %ld\n", startTime);

    const double scalingFactor = getScalingFactor(5, 10);
    printf("Time scale: %f\n", scalingFactor);

    // usleep(2500);
    // printf("Should be 50%%: %d%%\n", getBuildProgress(startTime, buildTime));
    fakeBuildTarget(startTime, buildTime, buildTime, "myLib", 1, true, true);

    return 0;
}

// FUNCTION DEFINITIONS

void
usleep(int milliseconds)
{
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

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
    x = INTIAL_TIME_STEP_MS/seconds;
    y = 1.0/(nodes - 1.0);
    scalingFactor = 1.0/(pow(x, y));

    return scalingFactor;
}

void
fakeBuildTarget(long startTime, long buildTime, long targetBuildTimeMilliseconds, const char* targetName, int numSourceFiles, bool isLib, bool isStatic)
{
    // printf("build time: %d\n", (int)targetBuildTimeMilliseconds); // DEBUG
    double timeScalingFactor = getScalingFactor(4, (int)targetBuildTimeMilliseconds);
    int progress;
    // printf("scaling factor: %f\n", timeScalingFactor); // DEBUG
    int sleepTimeMilliseconds = INTIAL_TIME_STEP_MS;
    sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG

    printf("Scanning dependencies of target %s\n", targetName);
    usleep(sleepTimeMilliseconds);
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG
    printf("[%3d%%] Building C object %s.c.o\n", progress, targetName);
    sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(sleepTimeMilliseconds);
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG

    char targetNameLower[STRING_BUF_SIZE]; // (TODO) Don't like this static array size
    strcpy(targetNameLower, targetName);
    for (int i = 0; targetNameLower[i]; ++i) targetNameLower[i] = tolower(targetNameLower[i]);

    if(isLib && isStatic)
    {
        printf("[%3d%%] Linking C static library lib%s.a\n", progress, targetNameLower);
    }
    else if (isLib)
    {
        printf("[%3d%%] Linking C shared library lib%s.so\n", progress, targetNameLower);
    }
    else
    {
        printf("[%3d%%] Linking C executable %s\n", progress, targetName);
    }
    sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(sleepTimeMilliseconds);
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG

    printf("[%3d%%] Built target %s\n", progress, targetName);
}

int
getBuildProgress(long startTime, long buildTime)
{
    double numerator = getCurrentTimeStampMilliseconds() - startTime;
    double denominator = buildTime;
    int progress = numerator / denominator * 100.0;

    if(progress > 100) { progress = 100; }

    return progress;
}

// TYPE DEFINITIONS

struct folder
{
    const char folderName;
    struct folder* folderList[10];
    const char* fileList[];
};