#pragma once
#include"StopWatch.h"

namespace core
{
    template<typename TClock>
    class Profile
    {
    public:
        template <typename TFunc>
        nanos time(TFunc&& arFunc)
        {
            mStopWatch.start();
            arFunc();
            mStopWatch.stop();
            return mStopWatch.elapsed();
        }

        template<std::size_t Num, typename TFunc>
        nanos averageTime(TFunc&& arFunc)
        {
            auto lTotal{0};

            while(Num > 0)
            {
                lTotal += time(arFunc);
                --Num;
            }
            return lTotal/Num;
        }

    private:
        StopWatch<TClock> mStopWatch;
    };
}