//
//  TempLogStream.h
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//
//  Description: This class is derived from std::stringstream
//               in an effort to make the logging interface simple.
//               The lifespan of these objects are temporary,
//               when the object is deleted, the Logger is called.

#pragma once
#include "Logger.h"
#include <sstream>

using namespace std;

// forward declarations
class Logger;
enum class LogLevel;

//class declaration
class TempLogStream : public ostringstream
{
public:
	TempLogStream(Logger& oLogger, LogLevel logLevel, int lineNum);
	TempLogStream(const TempLogStream& ls);
	~TempLogStream();

private:
	Logger& m_logger;
	LogLevel m_logLevel;
	int m_lineNum;
};