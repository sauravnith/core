/*
 * FileLogger.h
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */

#pragma once
#include <logger/LoggerI.h>
#include <fstream>

namespace core
{
	class FileLogger : public LoggerI
	{
	public:
		FileLogger(const std::string& arName);
		~FileLogger();
		void log(const char* arData)override;
	private:
   	    std::ofstream mFileStream;
	};

}

