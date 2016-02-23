//
//  Logger.h
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//
#pragma once
#include <string>
#include <sstream>
#include <mutex>
#include <memory>
#include <fstream>

using namespace std;

enum LogLevel
{
	INFO = 0,
	WARNING,
	ERROR
};

class Logger;

class Logger
{
public:
	Logger(string filename);
	virtual ~Logger();

	void log(LogLevel level, string message);

private:
	mutex		m_mutex;
	ofstream	m_logFile;
};
