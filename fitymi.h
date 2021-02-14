/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetic
 */

// DEFINES

#define _POSIX_C_SOURCE 199309L // To use the timestamp function in a POSIX way

#define INTIAL_TIME_STEP_MS 1000.0
#define FORMAT_STRING_BUF_SIZE 100
#define TEMP_STRING_BUF_SIZE 50
#define MAX_TARGETS 10
#define MAX_SOURCE_FILES 20
#define MAX_TARGET_BUILD_TIME 300000 // 5 mins in ms

// Colours
#define COLOUR_GREEN "[0;32m"
#define COLOUR_BOLD_GREEN "[1;32m"
#define COLOUR_BOLD_BLUE "[1;34m"
#define COLOUR_BOLD_MAGENTA "[1;35m"


// FUNCTION DECLARATIONS

void
usleep(int milliseconds);


double
getCurrentTimeStampMilliseconds();

/**
 * Get factor to multiply the sleeping time by to get an exponentially larger build time as "source files" are put together
 * @param nodes number of steps to reach the desired build time
 * @param seconds the desired build time
 * @return scaling factor to multiply sleep time by each build step
 */
double
getScalingFactor(int nodes, double duration);

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
fakeBuildTarget(double startPercent, double targetPercent, double targetEndBuildTime, const char* targetName, int maxSourceFiles);

void
updateBuildProgress(double* startPercent, double buildPercent);

void
colourPrint(const char* text, const char* colour);

// TYPE DECLARATIONS

struct folder;