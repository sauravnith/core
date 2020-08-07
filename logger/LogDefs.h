#pragma once

//Is it better to support << as Logging usage ??
//some corner cases to support << logging
// when data should be flushed - destructor or store all data in stream and then process
#define STD_DEBUG(...)  Logger::instance().log(SinkType::STD,core::LogLevel::DEBUG,__FILE__,__LINE__, __VA_ARGS__)
#define STD_INFO(...)  Logger::instance().log(SinkType::STD,core::LogLevel::INFO,__FILE__,__LINE__, __VA_ARGS__)

#define FILE_DEBUG(...)  Logger::instance().log(SinkType::FILE,core::LogLevel::DEBUG,__FILE__,__LINE__, __VA_ARGS__)
#define FILE_INFO(...)  Logger::instance().log(SinkType::FILE,core::LogLevel::INFO,__FILE__,__LINE__, __VA_ARGS__)


