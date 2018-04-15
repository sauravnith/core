/*
 * Log.h
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */

#pragma once

#include <logger/Logger.h>
#include <logger/impl/FileLogger.h>
namespace core
{

static Logger gFileLogger( std::make_unique<FileLogger>("uCanWrite.log") );

#define FILE_LOG_DEBUG(...) gFileLogger.log(Logger::LogLevel::DEBUG,__VA_ARGS__);
#define FILE_LOG_INFO(...) gFileLogger.log(Logger::LogLevel::INFO,__VA_ARGS__);
#define FILE_LOG_WARN(...) gFileLogger.log(Logger::LogLevel::WARN,__VA_ARGS__);
#define FILE_LOG_ERROR(...) gFileLogger.log(Logger::LogLevel::ERROR,__VA_ARGS__);

}

