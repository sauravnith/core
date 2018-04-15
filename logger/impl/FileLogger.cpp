/*
 * FileLogger.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */

#include "FileLogger.h"

using namespace core;

FileLogger::FileLogger(const std::string& arName)
{
	mFileStream.open( arName.c_str(), std::ios_base::binary|std::ios_base::out );

	if( !mFileStream.is_open() )
	{
		throw(std::runtime_error("FileLogger: Unable to open file [Name:" + arName + "]" ));
	}
}

FileLogger::~FileLogger()
{
	if(mFileStream.is_open())
	{
		mFileStream.close();
	}
}

void FileLogger::log(const char* arData)
{
	mFileStream<<arData;
	mFileStream.flush();
}
