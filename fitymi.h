/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetic
 */

// DEFINES

#define _POSIX_C_SOURCE 199309L // To use the timestamp function in a POSIX way

#define SCANNING Scanning dependencies of target
#define BUILDING
#define LINKING
#define BUILT

#define TIME_START 0.1

// FUNCTION DECLARATIONS

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
 * Outputs the text for the fake build process for a given "file"
 */
void
fakeBuildFile();

// TYPE DECLARATIONS

struct folder;