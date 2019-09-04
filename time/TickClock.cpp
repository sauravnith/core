#include"TickClock.h"

using namespace core;

static uint64_t sCpuMHz = 0;
static uint64_t sAlignmentLimit = 1;
static uint64_t sNanoFactor = 1UL << 20; //2^20 to preserve accuracy

static bool sInit = TickClock::init();

uint64_t ticksToNanos(uint64_t arTicks)
{
    return (arTicks * sNanoFactor) >> 20;
}


bool TickClock::init()
{
    static book gIsInitialized{false};

    if(gIsInitialized) return;

    gIsInitialized = true;

    sCpuMHz =

}