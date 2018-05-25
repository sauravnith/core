#pragma once
#include <optional>
#include <array>

namespace core
{
    //similar behaviour as queue of fixed size FIFO
    template<typename TMsg, size_t TSize = 8>
    class CircularArray
    {
    public:
        CircularArray()
        {}

        CircularArray(const CircularArray& arArray)
        {
            mArray = arArray.mArray;
            mReadIndex = arArray.mReadIndex;
            mWriteIndex = arArray.mWriteIndex;
        }

        CircularArray& operator=(CircularArray arArray)
        {
            swap(*this, arArray);
            return * this;
        }


        CircularArray(CircularArray&& arArray)noexcept:
                CircularArray()//calling default constructor
        {
            swap(*this, arArray);
        }

        CircularArray& operator=(CircularArray&& arArray)noexcept
        {//no need for self assignment check
            CircularArray lTemp(std::move(arArray));

            swap(*this, lTemp);

            return *this;
        }

        friend void swap (CircularArray& arRHS , CircularArray& arLHS) noexcept
        {
            //copy swap idiom
            std::swap(arRHS.mArray, arLHS.mArray);
            std::swap(arRHS.mReadIndex,arLHS.mReadIndex);
            std::swap(arRHS.mWriteIndex,arLHS.mWriteIndex);
        }


        size_t capacity()const { return mArray.size(); }

        size_t size()const { return (mWriteIndex-mReadIndex); }

        bool empty()const {  return mReadIndex == mWriteIndex ;}

        bool full()const { return size() == capacity();}

        void push(TMsg arMsg)
        {
            if(full())
            {
                throw std::runtime_error("Failed to push element as no space available");
            }

            mArray[writeIndex()] = arMsg;
            ++mWriteIndex;
        }

        void emplace_push(TMsg&& arMsg)
        {
            if(full())
            {
                throw std::runtime_error("Failed to push element as no space available");
            }

            mArray[writeIndex()] = std::move(arMsg);
            ++mWriteIndex;
        }

        std::optional<TMsg> pop()
        {
            if(empty())
            {
                return {};
            }

            std::optional<TMsg>lReturnValue(std::in_place, mArray[readIndex()]);
            ++mReadIndex;

            return lReturnValue;
        }

   private:
        std::array<TMsg,TSize>mArray;

        //assuming integer overflow will bring it back to 0
        int32_t mReadIndex{0};
        int32_t mWriteIndex{0};

        int32_t readIndex()const { return mReadIndex % capacity();}
        int32_t writeIndex()const { return mWriteIndex % capacity();}

    };
}
