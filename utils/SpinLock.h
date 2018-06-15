#pragma once
#include <atomic>

namespace core
{
    class SpinLock
    {
    public:
        SpinLock() = default;
        SpinLock(const SpinLock& ) = delete;
        SpinLock& operator=(const SpinLock&) = delete;

        //move
        SpinLock(SpinLock&& arSpinLock )noexcept;
        SpinLock& operator=(SpinLock&& arSpinLock )noexcept;

        void lock();
        void unlock();
    private:
        constexpr static int CACHE_LINE_SIZE{64};// on x86
        alignas(CACHE_LINE_SIZE)std::atomic_flag<> mFlag{ATOMIC_FLAG_INIT};
    };
}





