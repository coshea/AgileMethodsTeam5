//
//  TempLogStream.cpp
//  GEDCOM
//
//  Created by William MacDowell on 2/22/16.
//  Copyright © 2016 William MacDowell. All rights reserved.
//
//  See TempLogStream.h for a description of this class.

#include "TempLogStream.h"

TempLogStream::TempLogStream(Logger& logger, LogLevel logLevel, int lineNum) :
	m_logger(logger), m_logLevel(logLevel), m_lineNum(lineNum)
{
}

TempLogStream::TempLogStream(const TempLogStream& tls) :
	m_logger(tls.m_logger), m_logLevel(tls.m_logLevel), m_lineNum(tls.m_lineNum)
{
}

TempLogStream::~TempLogStream()
{
	m_logger.log(m_logLevel, m_lineNum, str());
}
