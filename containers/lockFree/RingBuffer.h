#pragma once
#include<atomic>
#include<functional>

namespace core
{
    // On x86(strong memory model) will generate memory fence after every store
    // Use accquire release semantics to produce minimal fencing
    template<typename TMsg, size_t TSize = 16>
    class RingBuffer
    {
    public:
        static_assert((TSize !=0),"Buffer size cannot be zero");

        //having buffer size power 2 allows us to use cheaper & operation instead of modulo
        static_assert(((TSize & (TSize -1)) == 0), "BufferSize should be power of 2" );


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

        }

        void push(const TMsg& arMsg)
        {
            TMsg lMsg(arMsg);

            emplace_push(std::move(lMsg));
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

            mArray[lWriteIndex & mBitMask ] = std::move(arMsg);

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

            TMsg lMsg(std::move(mArray[lReadIndex & mBitMask ]));

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

            arFunc(mArray[lReadIndex & mBitMask ]);

            mReadIndex.store(lReadIndex + 1 , std::memory_order_release);
        }

        //how much it can store
        size_t capacity()const { return TSize;}

        size_t size()const { return mWriteIndex.load(std::memory_order_acquire) - mReadIndex.load(std::memory_order_acquire); }

        bool empty()const { return mWriteIndex.load(std::memory_order_acquire) == mReadIndex.load(std::memory_order_acquire); }

        bool full()const { return size() == capacity(); }

    private:
        constexpr static size_t mBitMask = TSize -1;

        constexpr static int CACHE_LINE_SIZE{64};// on x86

        //aligning to prevent false sharing
        alignas(CACHE_LINE_SIZE)std::array<TMsg,TSize>mArray;

        alignas(CACHE_LINE_SIZE)std::atomic<int> mReadIndex{0};

        alignas(CACHE_LINE_SIZE)std::atomic<int> mWriteIndex{0};

    };
}


