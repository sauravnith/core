/*
 * main.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: sauravsharma
 */
#include <iostream>

#include <logger/Log.h>

using namespace core;

int main ()
{
    int a{16};
	FILE_LOG_DEBUG("yes it works ", a," ",10);
	FILE_LOG_INFO("yes it works ", 4," ",10.0);
	FILE_LOG_WARN("yes it works ", 4," ",10.1);
	FILE_LOG_ERROR("yes it works ", 4," ",10.2);
}



