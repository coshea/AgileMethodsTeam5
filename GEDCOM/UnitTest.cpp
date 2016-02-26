//
//  UnitTest.cpp
//  GEDCOM
//
//  Created by william.macdowell on 2/25/16.
//

#include <memory>
#include <thread>
#include <list>
#include "UnitTest.h"
#include "Logger.h"

Logger TestLog("TestLog.log");

static void Us40Us44Test();
void threadHandle(int threadID);

void UnitTestMain()
{
	Us40Us44Test();

	//TODO - Add unit tests for your stories here
}

//Test the multi-threaded capability of the Logger
//Test the ability to log line numbers
static void Us40Us44Test()
{
	list<shared_ptr<thread>> threadList;

	// create 50 threads
	for (int i = 0; i < 50; i++)
	{
		threadList.push_back(shared_ptr<thread>(new thread(threadHandle, i)));
	}

	// bring in all the threads before returning
	for (auto thread : threadList)
	{
		thread->join();
	}
}

// The thread function
void threadHandle(int threadID)
{
	// Write 50 lines of errors per thread
	for (int i = 0; i < 50; i++)
	{
		TestLog(LogLevel::ERROR, i) << "Thread " << threadID;
	}
}