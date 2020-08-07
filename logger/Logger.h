#pragma once
#include"LogDefs.h"
#include"Sink.h"
#include<array>

namespace core
{
    class Logger
    {
    public:
        static Logger& instance(){
            static Logger gLogger;
            return gLogger;
        }

        void setLogLevel(LogLevel arLevel) { mLogLevel = arLevel; }

        template<typename ...Args>
        void log(SinkType arSinkType, LogLevel arLevel, const char* arFile, int arLine, Args... arArgs){
            if(arLevel < mLogLevel || arSinkType > mSinkArray.size() ){
                return;
            }

            //default is std
            if( mSinkArray[arSinkType] == nullptr){
                arSinkType = SinkType::STD;
            }

            mSinkArray[arSinkType]->log(arLevel,arFile,arLine,arArgs...);
        }

     private:
        //by default add std sink
        Logger();

        LogLevel mLogLevel;
        //using index as key to get Sink
        std::array<Sink::Ptr, SinkType::NONE> mSinkArray;
    };
}
