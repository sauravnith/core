#pragma once
#include<utils/Types.h>
#include<time.h>

namespace core
{
    class OSClock
    {
    public:
        using duration = nanos;
        using rep = typename duration::rep;
        using period = typename duration::period;
        using time_point = typename std::chrono::time_point<OSClock>;

        static const bool is_steady = false;

        static time_point now() noexcept
        {
            struct timespec tp;
            clock_gettime(CLOCK_REALTIME,&tp);
            const auto lNanos = duration{tp.tv_sec * SECS_TO_NANOS + tp.tv_nsec};

            return time_point(std::chrono::duration_cast<duration>(lNanos));
        }
    };
}
