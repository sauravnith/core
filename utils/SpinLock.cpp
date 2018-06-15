#include "SpinLock.h"

using namespace core;

SpinLock::SpinLock(SpinLock&& arSpinLock ):mFlag(std::move(arSpinLock.mFlag))
{

}

SpinLock& SpinLock::operator=(SpinLock&& arSpinLock )
{
    mFlag = std::move(arSpinLock.mFlag);
}

void SpinLock::lock()
{
    while(mFlag.test_and_set(std::memory_order_acquire))
    {//number of threads competing for the lock increase its better to yeild
        //No need to call any of the below as scheduler will schedule thread to another core
        //sched_yeild: OS call- causes calling thread to relinquish CPU
        //mm_pause CPU call - no performance penalty reduces power consumption informs CPU it is a spinlock
        //                    allows hyper thread to be scheduled
        //asm("pause")
        //std::this_thread::yeild()

    }
}

void SpinLock::unlock()
{
    mFlag.clear(std::memory_release);
}



