/*
 * Logger.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: sauravsharma
 */

#include "Logger.h"

using namespace core;

Logger::Logger(LoggerI::Ptr arImplPtr):
	mLogPtr(std::move(arImplPtr))
{

}

void Logger::print()
{
	mStringStream<<"\n";

	mLogPtr->log(mStringStream.str().c_str());

	mStringStream.str("");
}

const char* Logger::logLevelToString(LogLevel arLevel)const
{
	switch(arLevel)
	{
	case LogLevel::DEBUG:
		return "DEBUG: ";
	case LogLevel::INFO:
		return "INFO:  ";
	case LogLevel::WARN:
		return "WARN:  ";
	case LogLevel::ERROR:
		return "ERROR: ";
	default:
		return "";
    }
}
