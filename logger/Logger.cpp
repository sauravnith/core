#include"Logger.h"

using namespace core;


Logger::Logger():
    mLogLevel{LogLevel::DEBUG}
{
    mSinkArray[SinkType::STD] = std::make_unique<StdSink<Sink>>();
}




