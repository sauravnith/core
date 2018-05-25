#pragma once
#include<atomic>
#include<functional>

namespace core
{
    //used for message passing between two threads : spsc queue
    // On x86(strong memory model) will generate memory fence after every store
    // Use accquire release semantics to produce minimal fencing
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
            swap(*this, arBuffer);
        }

        RingBuffer& operator=(RingBuffer&& arBuffer)noexcept
        {
            RingBuffer lTemp(std::move(arBuffer));//move constructor

            swap(*this, lTemp);

            return *this;
        }

        friend void swap(RingBuffer& arRHS, RingBuffer& arLHS)
        {
            std::swap(arRHS.mArray, arLHS.mArray);
            arRHS.mReadIndex = arLHS.mReadIndex;
            arRHS.mWriteIndex = arLHS.mWriteIndex;
        }

        void push(TMsg& arMsg)
        {
            TMsg lMsg(arMsg);

            emplace_push(std::move(arMsg));
        }

        void emplace_push(TMsg&& arMsg)
        {
            //using fetch_Add introduces a lock
            auto lWriteIndex = mWriteIndex.load(std::memory_order_acquire);

            auto lReadIndex = mReadIndex.load(std::memory_order_acquire);

            //FULL
            if(lWriteIndex - lReadIndex == capacity())
            {
                throw std::runtime_error("RingBuffer: No space available");
            }

            mArray[lWriteIndex % capacity() ] = std::move(arMsg);

            mWriteIndex.store(lWriteIndex + 1 , std::memory_order_release);
        }

        TMsg pop()
        {
            auto lWriteIndex = mWriteIndex.load(std::memory_order_acquire);

            auto lReadIndex = mReadIndex.load(std::memory_order_acquire);

            //EMPTY
            if(lWriteIndex == lReadIndex)
            {
                throw std::runtime_error("RingBuffer: Empty");
            }

            TMsg lMsg(std::move(mArray[lReadIndex % capacity() ]));

            mReadIndex.store(lReadIndex + 1 , std::memory_order_release);

            return lMsg;
        }

        using TFunc = std::function<void (const TMsg&)>;
        void consume_one(TFunc& arFunc)
        {
            auto lWriteIndex = mWriteIndex.load(std::memory_order_acquire);

            auto lReadIndex = mReadIndex.load(std::memory_order_acquire);

            //EMPTY
            if(lWriteIndex == lReadIndex)
            {
                throw std::runtime_error("RingBuffer: Empty");
            }

            arFunc(mArray[lReadIndex % capacity() ]);

            mReadIndex.store(lReadIndex + 1 , std::memory_order_release);
        }

        //how much it can store
        size_t capacity()const { return TSize;}

        //how many elements it has
        size_t size()const { return mWriteIndex.load(std::memory_order_acquire) - mReadIndex.load(std::memory_order_acquire); }

        bool empty()const { return mWriteIndex.load(std::memory_order_acquire) == mReadIndex.load(std::memory_order_acquire); }

        bool full()const { return size() == capacity(); }

    private:
        constexpr static int CACHE_LINE_SIZE{64};// on x86

        alignas(CACHE_LINE_SIZE)std::array<TMsg,TSize>mArray;

        __attribute__ ((aligned(CACHE_LINE_SIZE)))
        std::atomic<int> mReadIndex{0};

        __attribute__ ((aligned(CACHE_LINE_SIZE)))
        std::atomic<int> mWriteIndex{0};

    };
}


