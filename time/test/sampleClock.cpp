#include<time/Clock.h>
#include<time/OSClock.h>
#include<time/Profile.h>

#include<log/Logger.h>

using namespace core;

int main()
{
    {
        auto now = Clock<realClock >::now();
        STD_DEBUG("RealClock:");
        STD_DEBUG("Nanos[", nsSinceEpoch(now),"]");
        STD_DEBUG("UTC:[", toUTC(now),"] Local:[", toLocalTime(now),"]");
    }
        STD_DEBUG("");
    {
        auto now = Clock<OSClock >::now();
        STD_DEBUG("OSClock:");
        STD_DEBUG("Nanos[", nsSinceEpoch(now),"]");
        STD_DEBUG("UTC:[", toUTC(now),"] Local:[", toLocalTime(now),"]");
    }
    STD_DEBUG("");
    STD_DEBUG("OSClock:", Profile::averageTime<100>(Clock<OSClock>::now)," cycles");
    STD_DEBUG("RealClock :", Profile::averageTime<100>(Clock<realClock>::now),"cycles");


}
