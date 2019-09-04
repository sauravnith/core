#pragma once
#include "Clock.h"

namespace core
{
    template<typename TClock>
    class StopWatch
    {
    public:
        void start() { mStart = TClock::now(); }
        void stop() { mStop = TClock::now(); }
        nanos elapsed() const { return mStop - mStart; }
    private:
        nanos mStart;
        nanos mStop;
    };
}