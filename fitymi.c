/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetics
 *
 * @todo need to make % complete relative to number of files being build rather than time
 */

// My headers
#include "fitymi.h"
#include "dictionary.h"

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> // For sleep
#include <time.h> // For nanosleep, and timestamping
#include <math.h>
#include <string.h> // For strcpy
#include <ctype.h> // For tolower

static const uint32_t dictSize = sizeof(dictionary) / sizeof(dictionary[0]);

int
main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL)); // Seed random number generator

    // Parse arguments
    long totalBuildTime = 1000;
    if (argc == 2)
    {
       totalBuildTime = strtol(argv[1], (char **)NULL, 10);
       totalBuildTime *= 1000;
    }
    const uint8_t maxTargets = 5; // (TODO) Make an argument
    const uint8_t maxSourceFiles = 5; // (TODO) Make an argument

    // Initialise constants
    const long buildStartTime = getCurrentTimeStampMilliseconds();
    int targetStartPercent = 0;
    // const int numTargets = rand() % maxTargets + 1;
    const int numTargets = 3;
    const int targetBuildPercent = 100 / numTargets;
    const double scalingFactor = getScalingFactor(numTargets, totalBuildTime);
    long targetBuildTime = INTIAL_TIME_STEP_MS;
    if(numTargets == 1) { targetBuildTime = totalBuildTime; }
    // double timeScalingFactor = getScalingFactor(1, buildTime);

    printf("Dictionary Size: %d\n", dictSize);
    printf("Start time: %d\n", targetStartPercent); // DEBUG
    printf("Time scaling factor: %f\n", scalingFactor); // DEBUG
    printf("Build time: %ldms\n", totalBuildTime); // DEBUG
    printf("Target build percent: %d%%\n", targetBuildPercent); // DEBUG
    printf("Number of targets: %d\n", numTargets); // DEBUG

    // Generate a random number of targets with random names pulled from a dictionary
    // Malloc array space for random number of targets
    // Fill array with randomly pulled names from dictionary
    // For all elements in the array build with exponentially scaling build time

    // printf("Should be 50%%: %d%%\n", updateBuildProgress(&targetStartPercent, buildTime));
    for(int i = 0; i < numTargets; i++)
    {
        const long targetStartTime = getCurrentTimeStampMilliseconds();
        printf("Target build time: %ld\n", targetBuildTime); // DEBUG
        const char* targetName = dictionary[rand() % dictSize];
        fakeBuildTarget(targetStartPercent, targetBuildPercent, targetBuildTime, targetName, maxSourceFiles);
        targetBuildTime *= scalingFactor;
        targetStartPercent += targetBuildPercent;
        printf("Target time taken to completion: %ld\n", (getCurrentTimeStampMilliseconds() - targetStartTime));
    }
    printf("Total time taken to completion: %ld\n", (getCurrentTimeStampMilliseconds() - buildStartTime));

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
fakeBuildTarget(
    int startPercent,
    int targetPercent,
    long targetBuildTimeMilliseconds,
    const char* targetName,
    int maxSourceFiles)
{
    const uint8_t numSourceFiles = rand() % maxSourceFiles + 1;
    int currentPercent = startPercent;
    printf("Current percent: %d\n", currentPercent);
    printf("Target percent: %d\n", targetPercent);
    bool isStatic = true;
    bool isLib = true;
    char text[FORMAT_STRING_BUF_SIZE];
    // printf("build time: %d\n", (int)targetBuildTimeMilliseconds); // DEBUG
    // double timeScalingFactor = getScalingFactor(4, (int)targetBuildTimeMilliseconds);
    // const long targetBuildStartTime = getCurrentTimeStampMilliseconds();
    long partBuildTime = targetBuildTimeMilliseconds / (numSourceFiles + 1);
    int partBuildPercent = targetPercent / (numSourceFiles + 1);
    printf("Part percent: %d\n", partBuildPercent);
    // printf("scaling factor: %f\n", timeScalingFactor); // DEBUG
    // int sleepTimeMilliseconds = INTIAL_TIME_STEP_MS;
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG

    sprintf(text, "Scanning dependencies of target %s\n", targetName);
    colourPrint(text, COLOUR_BOLD_MAGENTA);
    usleep(partBuildTime);

    updateBuildProgress(&currentPercent, partBuildPercent);
    printf("[%3d%%] ", currentPercent);
    if (isLib)
    {
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, targetName);
    }
    else
    {
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, "main");
    }
    colourPrint(text, COLOUR_GREEN);
    usleep(partBuildTime);

    for (int i = 1; i < numSourceFiles; i++)
    {
        // Build random number of source files with target name plus random names picked from dictionary
        // For source file need to follow pattern: TARGET_NAME/CMakeFiles/TARGETNAME.dir/SOURCE_FILE_NAME.c.o
        updateBuildProgress(&currentPercent, partBuildPercent);
        // printf("Progress: %d\n", currentPercent); // DEBUG
        printf("[%3d%%] ", currentPercent);
        const char* sourceFileName = dictionary[rand() % dictSize];
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, sourceFileName);
        colourPrint(text, COLOUR_GREEN);
        // sleepTimeMilliseconds *= timeScalingFactor;
        // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
        usleep(partBuildTime);
    }

    char targetNameLower[TEMP_STRING_BUF_SIZE]; // (TODO) Don't like this static array size
    strcpy(targetNameLower, targetName);
    for (int i = 0; targetNameLower[i]; ++i) targetNameLower[i] = tolower(targetNameLower[i]);

    updateBuildProgress(&currentPercent, partBuildPercent);
    // printf("Progress: %d\n", currentPercent); // DEBUG

    if(isLib && isStatic)
    {
        printf("[%3d%%] ", currentPercent);
        sprintf(text, "Linking C static library lib%s.a\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else if (isLib)
    {
        printf("[%3d%%] ", currentPercent);
        sprintf(text, "Linking C shared library lib%s.so\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else
    {
        printf("[%3d%%] ", currentPercent);
        sprintf(text, "Linking C executable %s\n", targetName);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(partBuildTime);
    // printf("Progress: %d\n", currentPercent); // DEBUG

    printf("[%3d%%] ", currentPercent);
    printf("Built target %s\n", targetName);
}

void
updateBuildProgress(int* startPercent, long buildPercent)
{
    *startPercent += buildPercent;
    if(*startPercent > 100) { *startPercent = 100; }
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