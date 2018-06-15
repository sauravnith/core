#include <containers/lockFree/RingBuffer.h>
#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include<chrono>

using namespace std::chrono_literals;

struct TestMsg
{
    int mIndex;
    int mVal;
};


//check push/emplace_push
TEST(RingBufferTest,TestCase1)
{
    core::RingBuffer<TestMsg, 2> mRingBuffer;

    EXPECT_EQ(mRingBuffer.capacity(),2);
    EXPECT_EQ(mRingBuffer.size(),0);

    //PUSH ELEMENTS
    mRingBuffer.emplace_push({0,1});
    EXPECT_EQ(mRingBuffer.size(),1);

    mRingBuffer.emplace_push({1,2});
    EXPECT_EQ(mRingBuffer.size(),2);

    //FULL
    EXPECT_EQ(mRingBuffer.full(),true);
    ASSERT_THROW(mRingBuffer.emplace_push({2,3}), std::runtime_error);

    //POP
    auto lFirstMsg = mRingBuffer.pop();
    EXPECT_EQ(lFirstMsg.mIndex,0);
    EXPECT_EQ(lFirstMsg.mVal,1);

    EXPECT_EQ(mRingBuffer.full(),false);
    EXPECT_EQ(mRingBuffer.size(),1);

    //PUSH
    mRingBuffer.emplace_push({2,3});
    EXPECT_EQ(mRingBuffer.size(),2);

    //FULL
    EXPECT_EQ(mRingBuffer.full(),true);
    ASSERT_THROW(mRingBuffer.emplace_push({3,4}), std::runtime_error);

    //POP
    auto lSecondMsg = mRingBuffer.pop();
    EXPECT_EQ(lSecondMsg.mIndex,1);
    EXPECT_EQ(lSecondMsg.mVal,2);

    auto lThirdMsg = mRingBuffer.pop();
    EXPECT_EQ(lThirdMsg.mIndex,2);
    EXPECT_EQ(lThirdMsg.mVal,3);

    //EMPTY
    EXPECT_EQ(mRingBuffer.full(),false);
    EXPECT_EQ(mRingBuffer.empty(),true);

    ASSERT_THROW(mRingBuffer.pop(), std::runtime_error);
}

TEST(RingBufferTest,TestCase2)
{
    core::RingBuffer<TestMsg, 4> mRingBuffer;

    int lMaxCount{10};

    //create a thread - produces element till 10
    std::thread lProducer([&mRingBuffer,lMaxCount](){

        auto lFirstNum{0};
        auto lIndex{0};

        while(lFirstNum < lMaxCount)
        {
            try
            {
                mRingBuffer.emplace_push({lIndex,lFirstNum});

                ++lFirstNum;
            }
            catch(const std::exception& exception)
            {
                std::cout<<"Failed to add Error["<<exception.what()<<"]"<<std::endl;

                std::this_thread::sleep_for(1s);
            }

            ++lIndex;

        }
    });

    //consumer should get numbers in increasing order
    std::thread lConsumer([&mRingBuffer,lMaxCount](){

        auto lNum{0};

        while(lNum < lMaxCount)
        {
            try
            {
                auto lMsg = mRingBuffer.pop();

                EXPECT_EQ(lNum,lMsg.mVal);

                ++lNum;
            }
            catch(const std::exception& exception)
            {
                std::cerr<<"Failed to consume Error["<<exception.what()<<"]"<<std::endl;

                std::this_thread::sleep_for(1s);
            }
        }
    });

    lProducer.join();
    lConsumer.join();

    EXPECT_EQ(mRingBuffer.size(),0);
    EXPECT_EQ(mRingBuffer.empty(),true);
    EXPECT_EQ(mRingBuffer.capacity(),4);

}
