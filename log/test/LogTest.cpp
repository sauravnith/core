/*
 * main.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */
#include <log/Logger.h>

#include<vector>

using namespace core;

void swap(std::vector<int>& arInput, int lhs, int rhs)
{
    auto lTemp = arInput[rhs];
    arInput[rhs] = arInput[lhs];
    arInput[lhs] = lTemp;
}

int partition(std::vector<int>& arInput, int arStart, int arEnd)
{
    STD_DEBUG("Partition Start:",arStart," End:",arEnd);

    auto lElem = arInput[arStart];
    auto lStart = arStart + 1;

    while(lStart <= arEnd)
    {
        while(lStart <= arEnd && lElem >= arInput[lStart]) ++lStart;

        while(lStart <= arEnd && lElem <= arInput[arEnd]) --arEnd;

        if ( lStart < arEnd && lStart != arEnd ) swap(arInput, lStart,arEnd);
    }

    swap(arInput, lStart -1 , arStart);

    return lStart -1;

}

void quicksort(std::vector<int>& arInput, int arStart, int arEnd)
{
    if(arStart >= arEnd) return;

    auto random = std::rand()%(arEnd - arStart) + arStart;
    swap(arInput, arStart, random);

    auto pivot = partition(arInput, arStart,arEnd);

    quicksort(arInput, arStart, pivot -1);
    quicksort(arInput, pivot +1, arEnd);

}
int main ()
{
    Logger::instance().setLogLevel(LogLevel::INFO);
	STD_DEBUG("Hello World \n");

	std::vector<int> lInput{2,1,5,4,3};
    quicksort(lInput,0, lInput.size() - 1);

    for(const auto& num : lInput)
    {
        STD_INFO(num," ");
    }
    FILE_DEBUG("should not write or crash");
    FILE_INFO("should not write to std");
    //TODO this is not a test case
    //once logger is complete test all diff sinks and speed of writing
    //need PerTimer and time class
}



