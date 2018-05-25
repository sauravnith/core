#pragma once
#include<atomic>

namespace core
{
    //used for message passing between two threads : spsc queue
    template<typename TMsg, size_t TSize = 10>
    class RingBuffer
    {
    public:
        RingBuffer()=default;
        //atomics are moveable
        RingBuffer(const RingBuffer& arBuffer)=delete;
        RingBuffer& operator=(const RingBuffer& arBuffer)=delete;

        RingBuffer(RingBuffer&& arBuffer)noexcept
                :RingBuffer()
        {
            std::swap(mArray, arBuffer.mArray);
            std::swap(mReadIndex,arBuffer.mReadIndex);
            std::swap(mWriteIndex,arBuffer.mWriteIndex);
        }

        RingBuffer& operator=(RingBuffer&& arBuffer)noexcept
        {
            mArray = std::move(arBuffer.mArray);
            std::swap(mReadIndex,arBuffer.mReadIndex);
            std::swap(mWriteIndex,arBuffer.mWriteIndex);

            return *this;
        }

     /*   void put(TMsg& theMsg);

        TMsg get();

        template<typename TFunc>
        bool consume_one(TFunc& arFunc);

        template<typename TFunc>
        bool consume_all(TFunc& arFunc);

        //how much it can store
        size_t capacity()const { return TSize;}

        //how many elements it has
        size_t size()const { return mWriteIndex - mReadIndex; }

        bool empty()const { return mWriteIndex == mReadIndex; }
        bool full()const { return size() == capacity(); }
*/
    private:
        constexpr int CACHE_LINE_SIZE = 64;//in bytes on x86

        __attribute__ ((aligned(CACHE_LINE_SIZE)))
        std::array<TMsg,TSize>mArray;

        __attribute__ ((aligned(CACHE_LINE_SIZE)))
        std::atomic<int> mReadIndex;

        __attribute__ ((aligned(CACHE_LINE_SIZE)))
        std::atomic<int> mWriteIndex;
    };
}


