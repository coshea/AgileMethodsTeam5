//
//  Logger.h
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//
//  See Logger.h for a description of this class.

#include "Logger.h"

using namespace std;

Logger::Logger(string filename)
{
	m_logFile.open(filename, fstream::out | fstream::app | fstream::ate);
}

Logger::~Logger()
{
	m_logFile.flush();
	m_logFile.close();
}

TempLogStream Logger::operator()()
{
	return TempLogStream(*this, LogLevel::INFO, 0);
}

TempLogStream Logger::operator()(LogLevel logLevel, int lineNum)
{
	return TempLogStream(*this, logLevel, lineNum);
}

void Logger::log(LogLevel logLevel, int lineNum, string message)
{
	string loglevelstr = "";

	switch (logLevel)
	{
	case LogLevel::INFO:
		loglevelstr = "INFO";
		break;
	case LogLevel::WARNING:
		loglevelstr = "WARNING";
		break;
	case LogLevel::ERROR:
		loglevelstr = "ERROR";
		break;
	case LogLevel::DEBUG:
		loglevelstr = "DEBUG";
		break;
	default: // should not occur
		loglevelstr = "UNKNOWN";
		break;
	}

	m_mutex.lock();
	m_logFile << "Line " << lineNum << 
			" ("<< loglevelstr << ")\t" << 
			message << endl;
	m_mutex.unlock();
}
