#pragma once
#include<iostream>
#include<sstream>
#include<memory>

namespace core
{
    enum SinkType{
        STD = 0,
        FILE,
        NONE
    };

    enum LogLevel{
        DEBUG = 1,
        INFO,
        ERROR
    };

    class Sink
    {
    public:
        using Ptr = std::unique_ptr<Sink>;

        template<typename ...Args>
        void log(LogLevel arLevel, const char* arFile , int arLine, Args... arArgs){
            mStream.str("");
            format(arLevel,arFile,arLine);

            log(arArgs...);
        }

    protected:
        std::stringstream mStream;
    private:
        void format(LogLevel arLevel,const char* arFile,int arLine);

        //base case of recursion
        virtual void log() {};

        template<typename TFirst, typename ...Args>
        void log(TFirst arFirst, Args... arArgs)
        {
            mStream<<arFirst;
            log(arArgs...);
        }
    };

    //TODO create Async Sink
    //TODO File sink with policy - daily rolling,size rolling

    template<typename TSink>
    class StdSink : public TSink
    {
    private:
        void log()override final{
            std::cout<<TSink::mStream.str()<<std::endl;
        }
    };
}
