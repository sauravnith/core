#include<time/Clock.h>
#include<log/Logger.h>
using namespace core;

int main()
{
    auto now = Clock<realClock >::now();
    STD_DEBUG("Time now: ", nsSinceEpoch(now));
}
