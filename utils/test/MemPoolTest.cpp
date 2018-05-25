#include <utils/MemoryPool.h>
#include <gtest/gtest.h>


class TestClass
{
  public:
    TestClass(int& arTestVal):mTestVal(arTestVal)
    {
        //setting value  construction
        mTestVal = mTestVal*2;
    }
    ~TestClass()
    {
        //setting value  destruction
        mTestVal = mTestVal*2;
    }

  private:
    int& mTestVal;
};

class MemPoolTest: public testing::Test
{
  public:
    virtual ~MemPoolTest() = default;
    core::MemoryPool<TestClass, 2> mMemoryPool;
};

//check constructor/destructor call on allocating an object
//check size and available slots on memory
TEST_F(MemPoolTest,TestCase1)
{
    int lTestValue{1};

    {
        //inital capacity of memory poo;
        EXPECT_EQ(mMemoryPool.getCapacity(),2);
        EXPECT_EQ(mMemoryPool.getAvailable(),2);

        //create Object
        auto ltestClassPtr = mMemoryPool.allocateObject(lTestValue);
        //construction should set value
        EXPECT_EQ(lTestValue, 2);

        EXPECT_EQ(mMemoryPool.getCapacity(),2);
        EXPECT_EQ(mMemoryPool.getAvailable(),1);
    }

    //destruction should set value
    EXPECT_EQ(lTestValue, 4);

    EXPECT_EQ(mMemoryPool.getAvailable(),2);
}

//check behaviour when memory pool has no available slots

TEST_F(MemPoolTest,TestCase2)
{
    int lTestValue1{1},lTestValue2{2},lTestValue3{4};

    {
        //create Object
        auto ltestClassPtr1 = mMemoryPool.allocateObject(lTestValue1);

        auto ltestClassPtr2 = mMemoryPool.allocateObject(lTestValue2);

        EXPECT_EQ(mMemoryPool.getAvailable(),0);

        auto ltestClassPtr3 = mMemoryPool.allocateObject(lTestValue3);

        EXPECT_EQ(mMemoryPool.getAvailable(),0);
    }

    //size of memory pool should increase
    EXPECT_EQ(mMemoryPool.getAvailable(),3);

    //memory pool should have grown
    EXPECT_GT(mMemoryPool.getCapacity(),2);

    EXPECT_EQ(lTestValue1, 4);
    EXPECT_EQ(lTestValue2, 8);
    EXPECT_EQ(lTestValue3, 16);
}

