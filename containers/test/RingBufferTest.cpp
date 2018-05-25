#include <containers/lockFree/RingBuffer.h>
#include <gtest/gtest.h>

struct TestMsg
{
    int mIndex;
    int mVal;
};


//check push/emplace_push
TEST(CircularArrayTest,TestCase1)
{
    core::RingBuffer<TestMsg, 2> mRingBuffer;


}
