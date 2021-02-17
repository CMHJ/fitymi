/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetics
 *
 * @todo need to make % complete relative to number of files being build rather than time
 */

// Defines
#define _POSIX_C_SOURCE 199309L // To use the timestamp function in a POSIX way

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h> // For sleep
#include <time.h> // For nanosleep, and timestamping
#include <math.h>
#include <string.h> // For strcpy
#include <ctype.h> // For tolower

// My headers
#include "fitymi.h"

// External variables
extern const char* dictionary[];
extern const uint32_t dictSize;

int
main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL)); // Seed random number generator

    // Parse arguments
    double totalBuildTime = 10000.0;
    if (argc == 2)
    {
       totalBuildTime = strtol(argv[1], (char **)NULL, 10);
       totalBuildTime *= 1000.0; // Convert to ms
    }
    // const uint8_t maxTargets = MAX_TARGETS; // (TODO) Make an argument
    const uint8_t maxSourceFiles = MAX_SOURCE_FILES; // (TODO) Make an argument

    // Initialise constants
    const double buildStartTime = getCurrentTimeStampMilliseconds();
    int targetStartPercent = 0;
    // const int numTargets = rand() % maxTargets + 1;
    const uint8_t numTargets = 3;
    const double targetBuildPercent = 100.0 / (double)numTargets;
    // const double scalingFactor = getScalingFactor(numTargets, totalBuildTime);
    // double targetBuildTime = totalBuildTime / numTargets;
    // double targetBuildTime = INTIAL_TIME_STEP_MS;
    // if(numTargets == 1) { targetBuildTime = totalBuildTime; }
    // double timeScalingFactor = getScalingFactor(1, buildTime);
    double targetBuildTime;
    double targetEndBuildTime = buildStartTime;

    printf("Start time: %f\n", buildStartTime); // DEBUG
    // printf("Time scaling factor: %f\n", scalingFactor); // DEBUG
    printf("Total build time: %fms\n", totalBuildTime); // DEBUG
    printf("Target build percent: %f%%\n", targetBuildPercent); // DEBUG
    printf("Number of targets: %d\n", numTargets); // DEBUG

    // Generate a random number of targets with random names pulled from a dictionary
    // Malloc array space for random number of targets
    // Fill array with randomly pulled names from dictionary
    // For all elements in the array build with exponentially scaling build time

    // printf("Should be 50%%: %d%%\n", updateBuildProgress(&targetStartPercent, buildTime));
    uint32_t* targetBuildTimes = generateConstrainedRandomNumberSet(numTargets, totalBuildTime);
    for(int i = 0; i < numTargets; i++)
    {
        targetBuildTime = targetBuildTimes[i];

        const double targetStartTime = getCurrentTimeStampMilliseconds(); // DEBUG
        printf("\nTarget build time: %f\n", targetBuildTime); // DEBUG

        targetEndBuildTime += targetBuildTime;
        const char* targetName = dictionary[rand() % dictSize];
        fakeBuildTarget(targetStartPercent, targetBuildPercent, targetEndBuildTime, targetName, maxSourceFiles);
        targetStartPercent += targetBuildPercent;

        printf("Target time taken to completion: %f\n", (getCurrentTimeStampMilliseconds() - targetStartTime)); // DEBUG
    }
    printf("Total time taken to completion: %f\n", (getCurrentTimeStampMilliseconds() - buildStartTime));

    free(targetBuildTimes);
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

double
getCurrentTimeStampMilliseconds()
{
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + _t.tv_nsec/1.0e6;
}

double
getScalingFactor(int nodes, double finalValue)
{
    double scalingFactor, x, y;
    x = INTIAL_TIME_STEP_MS/finalValue;
    y = 1.0/((double)nodes - 1.0);
    scalingFactor = 1.0/(pow(x, y));

    return scalingFactor;
}

void
fakeBuildTarget(
    double startPercent,
    double targetPercent,
    double targetEndBuildTime,
    const char* targetName,
    int maxSourceFiles)
{
    const uint8_t numSourceFiles = rand() % maxSourceFiles + 1;
    const uint8_t numOperations = numSourceFiles + 1;
    double currentPercent = startPercent;
    printf("Current percent: %f\n", currentPercent);
    printf("Target percent: %f\n", targetPercent);
    bool isStatic = rand() % 2;
    bool isLib = rand() % 2;
    char text[FORMAT_STRING_BUF_SIZE];
    // printf("build time: %d\n", (int)targetBuildTimeMilliseconds); // DEBUG
    // double timeScalingFactor = getScalingFactor(4, (int)targetBuildTimeMilliseconds);
    // const long targetBuildStartTime = getCurrentTimeStampMilliseconds();
    const double targetStartBuildTime = getCurrentTimeStampMilliseconds();
    double currentPartBuildTime = targetStartBuildTime;
    uint32_t* partBuildTimes = generateConstrainedRandomNumberSet(numOperations, (uint32_t)(targetEndBuildTime - targetStartBuildTime));
    // const double partBuildTime = (targetEndBuildTime - targetStartBuildTime) / (double)numOperations;
    const double partBuildPercent = targetPercent / (double)numOperations;
    printf("Part percent: %f\n", partBuildPercent);
    printf("Num operations: %d\n", numOperations);
    // printf("scaling factor: %f\n", timeScalingFactor); // DEBUG
    // int sleepTimeMilliseconds = INTIAL_TIME_STEP_MS;
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG

    sprintf(text, "Scanning dependencies of target %s\n", targetName);
    colourPrint(text, COLOUR_BOLD_MAGENTA);

    updateBuildProgress(&currentPercent, partBuildPercent);
    printf("[%3.0f%%] ", currentPercent);
    if (isLib)
    {
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, targetName);
    }
    else
    {
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, "main");
    }
    colourPrint(text, COLOUR_GREEN);
    // usleep(targetEndBuildTime - (numOperations - 1) * partBuildTime - getCurrentTimeStampMilliseconds());
    currentPartBuildTime += partBuildTimes[0];
    usleep(currentPartBuildTime - getCurrentTimeStampMilliseconds());

    for (int i = 1; i < numSourceFiles; i++)
    {
        // Build random number of source files with target name plus random names picked from dictionary
        // For source file need to follow pattern: TARGET_NAME/CMakeFiles/TARGETNAME.dir/SOURCE_FILE_NAME.c.o
        updateBuildProgress(&currentPercent, partBuildPercent);
        // printf("Progress: %d\n", currentPercent); // DEBUG
        printf("[%3.0f%%] ", currentPercent);
        const char* sourceFileName = dictionary[rand() % dictSize];
        sprintf(text, "Building C object CMakeFiles/%s.dir/%s.c.o\n", targetName, sourceFileName);
        colourPrint(text, COLOUR_GREEN);
        // sleepTimeMilliseconds *= timeScalingFactor;
        // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
        // usleep(targetEndBuildTime - (numOperations - 1 - i) * partBuildTime - getCurrentTimeStampMilliseconds());
        currentPartBuildTime += partBuildTimes[1];
        usleep(currentPartBuildTime - getCurrentTimeStampMilliseconds());
    }

    char targetNameLower[TEMP_STRING_BUF_SIZE]; // (TODO) Don't like this static array size
    strcpy(targetNameLower, targetName);
    for (int i = 0; targetNameLower[i]; ++i) targetNameLower[i] = tolower(targetNameLower[i]);

    updateBuildProgress(&currentPercent, partBuildPercent);
    // printf("Progress: %d\n", currentPercent); // DEBUG

    if(isLib && isStatic)
    {
        printf("[%3.0f%%] ", currentPercent);
        sprintf(text, "Linking C static library lib%s.a\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else if (isLib)
    {
        printf("[%3.0f%%] ", currentPercent);
        sprintf(text, "Linking C shared library lib%s.so\n", targetNameLower);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    else
    {
        printf("[%3.0f%%] ", currentPercent);
        sprintf(text, "Linking C executable %s\n", targetName);
        colourPrint(text, COLOUR_BOLD_GREEN);
    }
    // sleepTimeMilliseconds *= timeScalingFactor;
    // printf("build time to sleep: %d\n", sleepTimeMilliseconds); // DEBUG
    usleep(targetEndBuildTime - getCurrentTimeStampMilliseconds());
    // printf("Progress: %d\n", currentPercent); // DEBUG

    printf("[%3.0f%%] ", currentPercent);
    printf("Built target %s\n", targetName);
    free(partBuildTimes);
}

void
updateBuildProgress(double* startPercent, double buildPercent)
{
    *startPercent += buildPercent;
    if(*startPercent > 99.15) { *startPercent = 100; }
}

void
colourPrint(const char* text, const char* colour)
{
    printf("\033%s", colour);
    printf("%s", text);
    printf("\033[0m"); // Reset terminal output back to normal
}

uint32_t*
generateConstrainedRandomNumberSet(uint32_t n, uint32_t total)
{
    // Generate dividers and sort
    uint32_t arr2[n];
    arr2[0] = 0;
    uint32_t range[total-1];
    for (int i = 1; i < total; i++) range[i] = i;
    for (int i = 1; i < n; i++) arr2[i] = range[rand() % (total-2) + 1];
    qsort(arr2, n, sizeof(int32_t), cmpfunc);

    // Create array to return
    uint32_t* arr = malloc(sizeof(uint32_t) * n);
    for (int i = 1; i < n; i++) arr[i-1] = arr2[i];
    arr[n-1] = total;

    // Perform final subtraction and return
    for (int i = 0; i < 4; i++) printf("%d ", arr[i]);
    printf("\n");
    for (int i = 0; i < 4; i++) printf("%d ", arr2[i]);
    printf("\n");
    for (int i = 0; i < n; i++) arr[i] -= arr2[i];
    for (int i = 0; i < 4; i++) printf("%d ", arr[i]);
    printf("\n");
    return arr;
}

int
cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

// TYPE DEFINITIONS

struct folder
{
    const char folderName;
    struct folder* folderList[10];
    const char* fileList[];
};