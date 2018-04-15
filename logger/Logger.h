/*
 * Logger.h
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */

#pragma once
#include "LoggerI.h"
#include <sstream>

namespace core
{
	class Logger
	{
	public:

		enum LogLevel
		{
			DEBUG = 1,
			INFO,
			WARN,
			ERROR
		};

		Logger(LoggerI::Ptr arImplPtr);

		template<typename...Args>
		void log(LogLevel arLevel, Args... arArgs)
		{
			print(logLevelToString(arLevel), arArgs...);
		}

	private:
		LoggerI::Ptr mLogPtr;
		std::stringstream mStringStream;

		//vardiac templates unpack function arguments
		void print();

		template<typename First, typename...Rest>
		void print(First arParam, Rest...arArgs)
		{
			mStringStream<<arParam;

			print(arArgs...);
		}

		const char* logLevelToString(LogLevel arLevel)const;
	};

}


