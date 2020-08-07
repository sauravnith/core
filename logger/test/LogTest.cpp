/*
 * main.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */
#include <logger/Logger.h>
#include <utils/asm.h>
#include<thread>
#include<chrono>

using namespace core;


int main ()
{
    Logger::instance().setLogLevel(LogLevel::INFO);
	STD_DEBUG("Hello World \n");
   using namespace std::chrono_literals;

    auto lStartTick = core::rdtscp();
    std::this_thread::sleep_for(1s);
    auto lEndTick = core::rdtscp();

    STD_INFO("Ticks in a second", lEndTick - lStartTick);


    FILE_DEBUG("should not write or crash");
    FILE_INFO("should not write to std");
    //TODO this is not a test case
    //once logger is complete test all diff sinks and speed of writing
    //need PerTimer and time class
}





