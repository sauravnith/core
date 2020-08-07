# pragma once

#include<stdint.h>
#include<chrono>

namespace core
{
    using Port = uint16_t;
    using Cycles = uint64_t;

    using seconds = std::chrono::seconds;
    using millis = std::chrono::milliseconds;
    using micros = std::chrono::microseconds;
    using nanos = std::chrono::nanoseconds;

    using realClock = std::chrono::high_resolution_clock;
    using monoClock = std::chrono::steady_clock;

    constexpr int32_t SECS_TO_MILLIS = 1000;
    constexpr int32_t SECS_TO_NANOS  = SECS_TO_MILLIS * SECS_TO_MILLIS * SECS_TO_MILLIS;
};