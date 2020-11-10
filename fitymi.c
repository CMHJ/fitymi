/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetics
 */

// My headers
#include "fitymi.h"

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep
#include <time.h> // For nanosleep, and timestamping
#include <math.h>
#include <string.h> // For strcpy
#include <ctype.h> // For tolower

int
main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL)); // Seed random number generator

    // Parse arguments
    long buildTime = 100;
    if (argc == 2)
    {
       buildTime = strtol(argv[1], (char **)NULL, 10);
       buildTime *= 1000;
    }
    const int maxTargets        = 5; // (TODO) Make an argument
    // const int maxSourceFiles    = 5; // (TODO) Make an argument

    // Initialise constants
    const long startTime        = getCurrentTimeStampMilliseconds();
    const int numTargets        = rand() % maxTargets + 1;
    const double scalingFactor  = getScalingFactor(numTargets, buildTime);
    long targetBuildTime        = INTIAL_TIME_STEP_MS;
    if(numTargets == 1) { targetBuildTime = buildTime; }
    // double timeScalingFactor = getScalingFactor(1, buildTime);

    printf("Start time: %ld\n", startTime); // DEBUG
    printf("Time scaling factor: %f\n", scalingFactor); // DEBUG
    printf("Build time: %ld\n", buildTime); // DEBUG
    printf("Number of target: %d\n", numTargets); // DEBUG

    // Generate a random number of targets with random names pulled from a dictionary
    // Malloc array space for random number of targets
    // Fill array with randomly pulled names from dictionary
    // For all elements in the array build with exponentially scaling build time

    // printf("Should be 50%%: %d%%\n", getBuildProgress(startTime, buildTime));
    for(int i = 0; i < numTargets; i++)
    {
        long targetStartTime = getCurrentTimeStampMilliseconds();
        printf("Target build time: %ld\n", targetBuildTime); // DEBUG
        fakeCmakeBuildTarget(startTime, buildTime, targetBuildTime, "myLib", 1);
        targetBuildTime *= scalingFactor;
        printf("Target time taken to completion: %ld\n", (getCurrentTimeStampMilliseconds() - targetStartTime));
    }
    printf("Total time taken to completion: %ld\n", (getCurrentTimeStampMilliseconds() - startTime));

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
getScalingFactor(int nodes, int milliseconds)
{
    double scalingFactor, x, y;
    x = INTIAL_TIME_STEP_MS/milliseconds;
    y = 1.0/(nodes - 1.0);
    scalingFactor = 1.0/(pow(x, y));

    return scalingFactor;
}

void
fakeCmakeBuildTarget(long startTime, long buildTime, long targetBuildTimeMilliseconds, const char* targetName, int maxSourceFiles)
{
    bool isStatic = true;
    bool isLib = true;
    char text[FORMAT_STRING_BUF_SIZE];
    // printf("build time: %d\n", (int)targetBuildTimeMilliseconds); // DEBUG
    // double timeScalingFactor = getScalingFactor(4, (int)targetBuildTimeMilliseconds);
    // const long targetBuildStartTime = getCurrentTimeStampMilliseconds();
    long partBuildTime = targetBuildTimeMilliseconds / 3;
    int progress;
    // printf("scaling factor: %f\n", timeScalingFactor); // DEBUG
    // int sleepTimeMilliseconds = INTIAL_TIME_STEP_MS;
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG

    sprintf(text, "Scanning dependencies of target %s\n", targetName);
    colourPrint(text, COLOUR_BOLD_MAGENTA);
    usleep(partBuildTime);

    // Build random number of source files with target name plus random names picked from dictionary
    // For source file need to follow pattern: TARGET_NAME/CMakeFiles/TARGETNAME.dir/SOURCE_FILE_NAME.c.o
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG
    printf("[%3d%%] ", progress);
    sprintf(text, "Building C object %s/CMakeFiles/%s.dir/%s.c.o\n", targetName, targetName, targetName);
    colourPrint(text, COLOUR_GREEN);
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(partBuildTime);
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG

    char targetNameLower[TEMP_STRING_BUF_SIZE]; // (TODO) Don't like this static array size
    strcpy(targetNameLower, targetName);
    for (int i = 0; targetNameLower[i]; ++i) targetNameLower[i] = tolower(targetNameLower[i]);

    if(isLib && isStatic)
    {
        printf("[%3d%%] ", progress);
        sprintf(text, "Linking C static library lib%s.a\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else if (isLib)
    {
        printf("[%3d%%] ", progress);
        sprintf(text, "Linking C shared library lib%s.so\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else
    {
        printf("[%3d%%] ", progress);
        sprintf(text, "Linking C executable %s\n", targetName);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(partBuildTime);
    progress = getBuildProgress(startTime, buildTime);
    // printf("Progress: %d\n", progress); // DEBUG

    printf("[%3d%%] ", progress);
    printf("Built target %s\n", targetName);
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

void
colourPrint(const char* text, const char* colour)
{
    printf("\033%s", colour);
    printf("%s", text);
    printf("\033[0m"); // Reset terminal output back to normal
}

// TYPE DEFINITIONS

struct folder
{
    const char folderName;
    struct folder* folderList[10];
    const char* fileList[];
};