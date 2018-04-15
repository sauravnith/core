/*
 * LogPolicy.h
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */

#pragma once
#include <memory>

namespace core
{
	class LoggerI
	{
	public:
		using Ptr = std::unique_ptr<LoggerI>;
		virtual ~LoggerI() = default;
		virtual void log (const char* arData) = 0;
	};
}

