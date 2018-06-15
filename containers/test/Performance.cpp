#include<containers/lockFree/MpscQueue.h>
#include<containers/lockFree/RingBuffer.h>

#include<iostream>
#include<chrono>
#include<thread>
#include<exception>

using namespace core;

//TODO: run same on Mpsc queue, check with valgrind run with different queue size
// check google benchmark
int main()
{
    int lCount{1000'00'000};

    RingBuffer<int,65536> lSpscBuffer;

    auto lStart = std::chrono::high_resolution_clock::now();

    std::thread lProducer([&lSpscBuffer, lCount]()
            {
                auto lNumIterations{lCount};

                while(lNumIterations)
                {
                    try
                    {
                        lSpscBuffer.push(lNumIterations);
                        --lNumIterations;
                    }
                    catch(const std::exception& exception)
                    {}
                }
            });

    std::thread lConsumer([&lSpscBuffer, lCount]()
            {
                auto lNumIterations{lCount};

                while(lNumIterations)
                {
                    try
                    {
                        lSpscBuffer.pop();
                        --lNumIterations;
                    }
                    catch(const std::exception& exception)
                    {}
                }
            });

    lProducer.join();
    lConsumer.join();

    auto lEnd = std::chrono::high_resolution_clock::now();

    auto lTimeElapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(lEnd - lStart)).count();

    std::cout << "SPSC queue completed "<<lCount
              <<" iterations in " << lTimeElapsed << " ms. " << std::endl;
}



