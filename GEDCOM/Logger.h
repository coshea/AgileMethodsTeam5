//
//  Logger.h
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//
//  Description: This class handles the general logging functionality.
//                It uses a mutex for thread-safety and offers different
//                levels of logs for the caller to choose from.

#pragma once
#include "TempLogStream.h"
#include <string>
#include <mutex>
#include <fstream>

using namespace std;

// forward declaration
class TempLogStream;

// log message levels
enum class LogLevel 
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
};

// class declaration
class Logger
{
public:
	Logger(string filename);
	virtual ~Logger();

	void log(LogLevel logLevel, int lineNum, string message);

	TempLogStream operator()();
	TempLogStream operator()(LogLevel logLevel, int lineNum);

private:
	mutex		m_mutex;
	ofstream	m_logFile;
};