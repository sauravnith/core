#pragma once
#include <utils/Types.h>
#include <string>
#include <iomanip>
#include <sstream>

namespace core
{
    template<typename TClock>
    class Clock
    {
    public:
        using time_point = typename TClock::time_point;
        using duration  = typename TClock::duration;
        using rep = typename TClock::rep;

        static constexpr bool is_steady = TClock::is_steady;

        static time_point now() {
            return TClock::now();
        }

        static constexpr time_point from_time_t(std::time_t t) noexcept
        {
            const auto lFromPoint = std::chrono::time_point<Clock<TClock>, seconds>{seconds{t}};
            return std::chrono::time_point_cast<duration>(lFromPoint);
        }
    };

    template<typename TTimePoint>
    std::time_t to_time_t(TTimePoint arTimePoint) noexcept
    {
        //time_t: holding number of seconds since epoch
        return std::chrono::duration_cast<seconds>(arTimePoint.time_since_epoch()).count();
    }

    template<typename TDuration, typename TTimePoint>
    TDuration durationCast(TTimePoint arTimePoint){
        return std::chrono::duration_cast<TDuration>(arTimePoint.time_since_epoch());
    }

    template<typename TTimePoint>
    uint64_t nsSinceEpoch(TTimePoint arTimePoint){
        return durationCast<nanos,TTimePoint>(arTimePoint).count();
    }

    template<typename TTimePoint>
    uint64_t microsSinceEpoch(TTimePoint arTimePoint){
        return durationCast<micros,TTimePoint>(arTimePoint).count();
    }

    template<typename TTimePoint>
    uint64_t millisSinceEpoch(TTimePoint arTimePoint){
        return durationCast<millis,TTimePoint>(arTimePoint).count();
    }

    template<typename TTimePoint>
    std::string toLocalTime(TTimePoint arTimePoint)
    {
        auto lTime = to_time_t(arTimePoint);

        std::stringstream lStream;
        lStream<<std::put_time( std::localtime(&lTime), "%Y%m%d-%H:%M:%S");

        return lStream.str();
    }

    template<typename TTimePoint>
    std::string toUTC(TTimePoint arTimePoint)
    {
        auto lTime = to_time_t(arTimePoint);

        std::stringstream lStream;
        lStream<<std::put_time( std::gmtime(&lTime), "%Y%m%d-%H:%M:%S");

        return lStream.str();
    }
}
