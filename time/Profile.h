#pragma once
#include <utils/Types.h>
#include <utils/asm.h>

namespace core
{
    class Profile
    {
    public:
        template <typename TFunc>
        static Cycles time(TFunc arFunc)
        {
            const auto lStart = rdtscp();
            arFunc();
            const auto lEnd = rdtscp();
            return lEnd - lStart;
        }

        template<std::size_t Num, typename TFunc>
        static Cycles averageTime(TFunc arFunc)
        {
            auto lTotal{0};
            auto lNum{Num};

            while(lNum > 0)
            {
                lTotal += time(arFunc);
                --lNum;
            }
            return lTotal/Num;
        }
    };
}