#pragma once
#include<atomic>
#include<array>
#include<stdexcept>

/*
 * Bounded multiple producer single consumer queue
 * Use mMaxReadIdx to synchronize multiple producers
 * Producers need to commit data to be visible to consumer
 */
template<typename TMsg, std::size_t TSize = 16>
class MpscQueue
{
public:
    static_assert((TSize ==0),"Buffer size is empty");
    static_assert((TSize  & (TSize -1))==0,"Buffer size not power of 2");

    MpscQueue()=default;
    MpscQueue(const MpscQueue& arBuffer)=delete;
    MpscQueue& operator=(const MpscQueue& arBuffer)=delete;

    MpscQueue(MpscQueue&& arBuffer)=delete;
    MpscQueue& operator=(MpscQueue&& arBuffer)=delete;

    std::size_t capacity()const { return TSize;}
    std::size_t size()const { return mWriteIdx.load(std::memory_order_acquire) - mReadIdx.load(std::memory_order_acquire); }
    bool empty()const { return mWriteIdx.load(std::memory_order_acquire) == mReadIdx.load(std::memory_order_acquire); }
    bool full()const { return size() == capacity(); }

    void push(const TMsg& arMsg)
    {
        if(full())
        {
           throw std::runtime_error("Mpsc Queue is full");
        }

        auto lWriteIdx = mWriteIdx.load(std::memory_order_acquire);

        while(mWriteIdx.compare_exchange_weak(lWriteIdx,lWriteIdx +1,std::memory_order_acq_rel) == false)// try to claim the index both producer can try to claim concurrently
        {
            lWriteIdx = mWriteIdx.load(std::memory_order_acquire);
        }

        //slot has been claimed means it is reserved for one producer
        mArray[lWriteIdx& mBitMask] = arMsg;

        //commit move the MaxReadIndex ahead so that change gets visible to other consumers
        while(mMaxReadIdx.compare_exchange_weak(lWriteIdx , lWriteIdx +1, std::memory_order_acq_rel))
        {// wait till maxReadIndex reaches the claimed slot
            // std::this_thread::yeild() depend on how and many producers are configured Thinking about it should be policy decided by user ??
            // In case of less processors and more producers should call yeild()
        }
    }

    TMsg pop()
    {
        if(empty())
        {
            throw std::runtime_error("Mpsc queue is empty");
        }

        auto lReadIdx = mReadIdx.load(std::memory_order_acquire);
        auto lMaxReadIdx = mMaxReadIdx.load(std::memory_order_acquire);

        //Queue is not empty so producer is working on commiting the data, busy wait
        while(lReadIdx == lMaxReadIdx)
        {
            lReadIdx = mReadIdx.load(std::memory_order_acquire);
            lMaxReadIdx = mMaxReadIdx.load(std::memory_order_acquire);
        }

        TMsg lMsg{std::move(mArray[lReadIdx & mBitMask])};

        mReadIdx.store(lReadIdx +1, std::memory_order_release);

        return lMsg;
    }

private:
    constexpr static int mBitMask{TSize -1};
    constexpr static int CACHE_LINE_SIZE{64};

    //where new element will be inserted to
    alignas(CACHE_LINE_SIZE)std::atomic<int> mReadIdx;

    //where next element will be written
    alignas(CACHE_LINE_SIZE)std::atomic<int> mWriteIdx;

    //Points to last commited data Reader cannot go beyond
    alignas(CACHE_LINE_SIZE)std::atomic<int>mMaxReadIdx;

    alignas(CACHE_LINE_SIZE)std::array<TMsg,TSize>mArray;


};





