/**
 * Fake It Till You Make It
 * Fake compiler for fun that emulates different build systems for asthetic
 */

// Constants

#define SCANNING Scanning dependencies of target
#define BUILDING
#define LINKING
#define BUILT

#define TIME_START 0.1

/**
 * Get factor to multiply the sleeping time by to get an exponentially larger build time as "source files" are put together
 * @param nodes number of steps to reach the desired build time
 * @param seconds the desired build time
 * @return scaling factor to multiply sleep time by each build step
 */
double getScalingFactor(int nodes, int seconds);