//
//  Logger.cpp
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//

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

void Logger::log(LogLevel level, string message)
{
	string levelStr = "";

	switch (level)
	{
	case INFO:
		levelStr = "INFO";
		break;
	case WARNING:
		levelStr = "WARNING";
		break;
	case ERROR:
		levelStr = "ERROR";
		break;
	default:
		levelStr = "UNKNOWN";
		break;
	}

	m_mutex.lock();
	m_logFile << levelStr << "\t" << message << std::endl;
	m_mutex.unlock();
}