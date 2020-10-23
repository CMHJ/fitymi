/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetic
 */

// INCLUDES
#include <stdbool.h>

// DEFINES

#define _POSIX_C_SOURCE 199309L // To use the timestamp function in a POSIX way

#define INTIAL_TIME_STEP_MS 1.0

#define STRING_BUF_SIZE 50

// FUNCTION DECLARATIONS

void
usleep(int milliseconds);

long
getCurrentTimeStampMilliseconds();

/**
 * Get factor to multiply the sleeping time by to get an exponentially larger build time as "source files" are put together
 * @param nodes number of steps to reach the desired build time
 * @param seconds the desired build time
 * @return scaling factor to multiply sleep time by each build step
 */
double
getScalingFactor(int nodes, int seconds);

/**
 * Generate the fake file system to "build" full of files and folder
 */
void
generateFileSystemTree();

/**
 * Outputs the text for the fake build process for a given "target"
 * @param targetName
 * @param numSourceFiles
 * @param isLib
 * @param isStatic
 */
void
fakeBuildTarget(long startTime, long buildTime, long targetBuildTimeMilliseconds, const char* targetName, int numSourceFiles, bool isLib, bool isStatic);

int
getBuildProgress(long startTime, long buildTime);

// TYPE DECLARATIONS

struct folder;