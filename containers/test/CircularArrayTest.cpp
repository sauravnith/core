#include <containers/CircularArray.h>
#include <gtest/gtest.h>
#include <stdexcept>

struct TestMsg
{
    int mIndex;
    int mVal;
    //TODO add constructor and destructor and check operator = behaviour
};


//check push/emplace_push
TEST(CircularArrayTest,TestCase1)
{
    core::CircularArray<TestMsg, 2> mCircularArray;

    EXPECT_EQ(mCircularArray.capacity(),2);
    EXPECT_EQ(mCircularArray.size(),0);

    //PUSH ELEMENTS
    mCircularArray.emplace_push({0,1});
    EXPECT_EQ(mCircularArray.size(),1);

    mCircularArray.emplace_push({1,2});
    EXPECT_EQ(mCircularArray.size(),2);

    //FULL
    EXPECT_EQ(mCircularArray.full(),true);
    ASSERT_THROW(mCircularArray.emplace_push({2,3}), std::runtime_error);

    //POP
    auto lFirstMsg = mCircularArray.pop();
    EXPECT_EQ(lFirstMsg.value().mIndex,0);
    EXPECT_EQ(lFirstMsg.value().mVal,1);

    EXPECT_EQ(mCircularArray.full(),false);
    EXPECT_EQ(mCircularArray.size(),1);

    //PUSH
    mCircularArray.emplace_push({2,3});
    EXPECT_EQ(mCircularArray.size(),2);

    //FULL
    EXPECT_EQ(mCircularArray.full(),true);
    ASSERT_THROW(mCircularArray.emplace_push({3,4}), std::runtime_error);

    //POP
    auto lSecondMsg = mCircularArray.pop();
    EXPECT_EQ(lSecondMsg.value().mIndex,1);
    EXPECT_EQ(lSecondMsg.value().mVal,2);

    auto lThirdMsg = mCircularArray.pop();
    EXPECT_EQ(lThirdMsg.value().mIndex,2);
    EXPECT_EQ(lThirdMsg.value().mVal,3);

    //EMPTY
    EXPECT_EQ(mCircularArray.full(),false);
    EXPECT_EQ(mCircularArray.empty(),true);

    auto lMsg = mCircularArray.pop();
    ASSERT_THROW(lMsg.value(), std::bad_optional_access);
}
