/*
 * main.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */
#include <log/Logger.h>
#include <utils/asm.h>
#include<vector>
#include<thread>
#include<chrono>
#include<utils/traits.h>
#include<algorithm>

using namespace core;

void swap(std::vector<int>& arInput, int lhs, int rhs)
{
    auto lTemp = arInput[rhs];
    arInput[rhs] = arInput[lhs];
    arInput[lhs] = lTemp;
}


struct A
{
    int32_t a1;
    int64_t a2;
};

template<typename TMsg, typename TConvert>
void convert(TMsg& arMsg)
{

}

enum Endian
{
    LITTLE,
    BIG
};

namespace
{
    struct LittleEndian
    {
        template<typename Type>
        static void get(Type& arType);
    };

    struct BigEndian
    {
        template<typename Type>
        static void get(Type& arType);
    };

    template<typename Type>
    void BigEndian::get(Type& arType){}

    template<typename Type>
    void LittleEndian::get(Type& arType){}

    template<>
    void LittleEndian::get<int32_t>(int32_t & arType){
        STD_DEBUG("int32_t called");
    }

    template<>
    void LittleEndian::get<int64_t>(int64_t & arType){
        STD_DEBUG("int64_t called");
    }

    template<typename TMsg, typename TConvert>
    void convert(){}

    template<typename TMsg = A, typename TConvert>
    void convert(A& arMsg)
    {
        TConvert::get(arMsg.a1);
        TConvert::get(arMsg.a2);
    }
}
template<typename TMsg =A , Endian TEndian>
void convert(A& arMsg)
{
    TEndian == Endian::LITTLE ? convert<TMsg,LittleEndian>(arMsg) :
                                convert<TMsg, BigEndian>(arMsg);

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

void insertionsort(std::vector<int>& arInput)
{
   if(arInput.size() <=1)
   {
      return;
   }

   for(int lStart = 1; lStart < arInput.size(); ++lStart)
   {
       const auto lElem = arInput[lStart];

       auto lReverseStart = lStart -1;

       while(lReverseStart>=0 && arInput[lReverseStart] > lElem)
       {
           arInput[lReverseStart +1] = arInput[lReverseStart];

           --lReverseStart;
       }

       arInput[lReverseStart+1] = lElem;
   }
}

int max(const std::vector<int>& arVec, int arStart, int arEnd)
{
    auto lMaxIdx = arStart;
    ++arStart;

    while(arStart < arVec.size() && arStart <= arEnd)
    {
        if(arVec[arStart] > arVec[lMaxIdx])
            lMaxIdx = arStart;

        ++arStart;
    }

    return lMaxIdx;
}

void rotate(std::vector<int>& arVec , int arSrcIdx, int arEndIdx)
{
    STD_DEBUG("Rotating from  SrcIdx:",arSrcIdx," EndIdx:",arEndIdx);

    if(arEndIdx >= arVec.size())
    {
        STD_DEBUG("Failed to rotate");
        return;
    }

    auto lLastElem = arVec[arEndIdx];

    --arEndIdx;
    while(arEndIdx >=arSrcIdx)
    {
        arVec[arEndIdx +1] = arVec[arEndIdx];
        --arEndIdx;
    }

    arVec[arSrcIdx] = lLastElem;
}

std::vector<int>::iterator permute(std::vector<int>& arVec, std::vector<int>::iterator arStart, std::vector<int>::iterator arEnd)
{
    STD_DEBUG("calling permute Start: ", *arStart, " End:",*arEnd);

    auto lElems = std::distance(arStart, arEnd) + 1 ;

    if(lElems < 3 )
    {
        STD_DEBUG("Trying to run permute on less than 3 elements");
        return arVec.end();
    }

    auto lMaxIter = std::max_element(arStart, arStart +2);
    auto lMaxElem = *lMaxIter;

    auto lTry{0};

    while(lTry <3 && lMaxElem != *(arStart +2) )
    {
        std::rotate(arStart, arStart +1, arEnd + 1);
        ++lTry;
    }

    if(lTry == 3)
    {
        return arVec.end();
    }

    return arStart+2 ;
}

void permute(std::vector<int>& arVec)
{
    STD_DEBUG("Calling permute Input:");

    for(auto lNum : arVec)
    {
        STD_DEBUG("Num:", lNum);
    }

    auto lStart{arVec.begin()};
    auto lEnd {arVec.end() - 1};

    while(lStart < lEnd)
    {
        //move forward start
       while(lStart < lEnd && std::distance(arVec.begin(), lStart) == *lStart - 1)
        {     ++lStart;
        }

        //move end backward
        while(lEnd > arVec.begin() && std::distance(arVec.begin(),lEnd) == *lEnd - 1)
        {
            --lEnd;
        }

        auto lNewStart = lStart;

        while(lNewStart + 2 <= lEnd )
        {
            auto lMaxIdx = permute(arVec,lNewStart,lNewStart + 2);

            if(lMaxIdx == arVec.end())
            {
                STD_DEBUG("Unable to find MaxIdx");
                break;
            }

            auto lRemainingElem = lEnd - lMaxIdx  + 1;

            if(lRemainingElem == 2)
            {
                --lMaxIdx;
            }

            lNewStart = lMaxIdx;
        }

        if(lNewStart == lStart)
        {
            break;
        }
    }

    const auto lResult = lStart < lEnd ? "False" : "True";

    STD_DEBUG("Permute Result: ", lResult, " Output:");
    for(auto lNum : arVec)
    {
        STD_DEBUG("Num:", lNum);
    }
}
std::string biggerIsGreater(std::string w) {
    if(w.size() <=1 )
    {
        return "no answer";
    }

    auto lRevStart = w.rbegin();
    ++lRevStart;

    auto lLast{--w.end()};

    while(lRevStart != w.rend())
    {
        const auto lChar = *lRevStart;
        auto lGreaterElem = std::lower_bound(lLast,w.end(),lChar);

        if(lGreaterElem == w.end() || *lGreaterElem == lChar)
        {
            ++lRevStart;
            --lLast;
            w.erase(lLast);
            w.push_back(lChar);
            continue;
        }

        const auto lGreaterChar = *lGreaterElem;
        *lGreaterElem = lChar;
        *lRevStart = lGreaterChar;
        return w;

    }
    return "no answer";
}


int main ()
{
  //  Logger::instance().setLogLevel(LogLevel::INFO);
	STD_DEBUG("Hello World \n");


	//std::cout<<biggerIsGreater("zedawdvyyfumwpupuinbdbfndyehircmylbaowuptgmw")<<std::endl;

    /*std::cout<<biggerIsGreater("zyyxwwtrrnmlggfeb")<<std::endl;

    std::cout<<biggerIsGreater("ocsmerkgidvddsazqxjbqlrrxcotrnfvtnlutlfcafdlwiismslaytqdbvlmcpapfbmzxmftrkkqvkpflxpezzapllerxyzlcf")<<std::endl;

    std::cout<<biggerIsGreater("biehzcmjckznhwrfgglverxsezxuqpj")<<std::endl;
*/
	std::cout<<biggerIsGreater("ab")<<std::endl;
	std::cout<<biggerIsGreater("ghhba")<<std::endl;
    std::cout<<biggerIsGreater("aaaaaaaaaaaavvvvvb")<<std::endl;

	/*std::string lTemp{"hckd"};
	auto lLeftStart = lTemp.begin();
    std::advance(lLeftStart,lTemp.size() -2);

	std::sort(lTemp.end() -2, lTemp.end());
	std::cout<<lTemp<<std::endl;*/
 /*   {
        std::vector<int>lVctr{3,1,2,8,5,6,7,9,4};

        permute(lVctr);
    }

    {
        std::vector<int>lVctr{3,2,1};

        permute(lVctr);
    }

    {
        std::vector<int>lVctr{1,6,5,2,3,4};

        permute(lVctr);
    }
*/

	//std::cout<<"Vector: "<<core::is_iterator<std::vector<int>::iterator>::value <<std::endl;
	//std::cout<<"Int:"<<core::is_iterator<int>::value<<std::endl;
	//A a;

	//convert<A, Endian::LITTLE>(a);

/*	std::vector<int> lInput{5,4};

	for(auto i=0; i < 10 ; ++i)
    {
        auto lStartTick = core::rdtsc();
        //quicksort(lInput,0, lInput.size() - 1);
        insertionsort(lInput);
        auto lEndTick = core::rdtsc();

        STD_INFO("Ticks elapsed using rdtsc: ", lEndTick - lStartTick);
    }

	for(const auto& num : lInput)
    {
      STD_INFO(num," ");
    }
*/

  /*  for(auto i=0; i < 10 ; ++i)
    {
        auto lStartTick = core::rdtscp();
        //quicksort(lInput,0, lInput.size() - 1);
        insertionsort(lInput);
        auto lEndTick = core::rdtscp();

        STD_INFO("Ticks elapsed using rdtscp: ", lEndTick - lStartTick);
    }
*/
   /* using namespace std::chrono_literals;

    auto lStartTick = core::rdtscp();
    std::this_thread::sleep_for(1s);
    auto lEndTick = core::rdtscp();

    STD_INFO("Ticks in a second", lEndTick - lStartTick);
*/

   // FILE_DEBUG("should not write or crash");
   // FILE_INFO("should not write to std");
    //TODO this is not a test case
    //once logger is complete test all diff sinks and speed of writing
    //need PerTimer and time class
}

#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int max(const vector<int>& arVec, int arStart, int arEnd)
{
    auto lMaxIdx = arStart;
    ++arStart;

    while(arStart < arVec.size() && arStart <= arEnd)
    {
        if(arVec[arStart] > arVec[lMaxIdx])
            lMaxIdx = arStart;

        ++arStart;

    }

    return lMaxIdx;
}

void rotate(vector<int>& arVec , int arSrcIdx, int arEndIdx)
{
    if(arEndIdx >= arVec.size())
    {
        //STD_DEBUG("Failed to rotate");
        return;
    }

    auto lLastElem = arVec[arEndIdx];

    --arEndIdx;
    while(arEndIdx >=arSrcIdx)
    {
        arVec[arEndIdx +1] = arVec[arEndIdx];
        --arEndIdx;
    }

    arVec[arSrcIdx] = lLastElem;
}

int permute(std::vector<int>& arVec, int arStart, int arEnd)
{
    //STD_DEBUG("calling permute Start:", arStart , " End:",arEnd);

    auto lElems = arEnd - arStart +1;

    if(lElems < 3 )
    {
        //STD_DEBUG("Trying to run permute on less than 3 elements");
        return -1;
    }

    auto lMaxIdx = max(arVec,arStart, arStart +2);
    auto lMaxElem = arVec[lMaxIdx];

    auto lTry{0};

    while(lTry <3 && lMaxElem != arVec[arStart +2])
    {
        rotate(arVec,arStart, arStart +2);
        ++lTry;
    }

    if(lTry ==3)
    {
        return -1;
    }

    return arStart +2;
}

string permute(std::vector<int>& arVec)
{
    //STD_DEBUG("Calling permute Input:");

    /*for(auto lNum : arVec)
    {
        STD_DEBUG("Num:", lNum);
    }*/

    int lStart{0};
    int lEnd = arVec.size() -1;

    while(lStart < lEnd)
    {
        //move forward start
        while(lStart < arVec.size() && lStart == arVec[lStart] - 1)
        {
            ++lStart;
        }

        //move end backward
        while(lEnd >=0 && lEnd == arVec[lEnd] - 1)
        {
            --lEnd;
        }

        auto lNewStart = lStart;

        while(lNewStart < lEnd )
        {
            auto lMaxIdx = permute(arVec,lNewStart,lEnd);

            if(lMaxIdx == -1)
            {
                //STD_DEBUG("Unable to find MaxIdx");
                break;
            }

            auto lRemainingElem = lEnd - lMaxIdx  + 1;

            if(lRemainingElem == 2)
            {
                --lMaxIdx;
            }

            lNewStart = lMaxIdx;
        }

        if(lNewStart == lStart)
        {
            break;
        }
    }

    const auto lResult = lStart < lEnd ? "NO" : "YES";

    //STD_DEBUG("Permute Result: ", lResult, " Output:");
    /*for(auto lNum : arVec)
    {
        STD_DEBUG("Num:", lNum);
    }*/

    return lResult;
}


// Complete the larrysArray function below.
string larrysArray(vector<int> A) {
    return permute(A);

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string A_temp_temp;
        getline(cin, A_temp_temp);

        vector<string> A_temp = split_string(A_temp_temp);

        vector<int> A(n);

        for (int i = 0; i < n; i++) {
            int A_item = stoi(A_temp[i]);

            A[i] = A_item;
        }

        string result = larrysArray(A);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

#endif



