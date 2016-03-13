//
//  Date.h
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef Date_h
#define Date_h

#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>

using namespace std;

class Date
{
public:
    
    Date();
    
    // contructor
    Date(int d, int m, int y);

	// contructor
	Date(string d, string m, string y);
    
    void setMonth(int m);
    
    int getMonth();
    
    void setDay(int d);
    
    int getDay();
    
    void setYear(int y);
    
    int getYear();
    
    string toString();
    
    string monthToString(int m);

	int stringToMonth(string m);

	bool isInPast();

	bool isDateValid();

	bool occursAfter(Date target);
	void AddMonths(int number);
	bool operator==(const Date& d1) const;
	bool operator>(const Date& d1) const;
	bool operator<(const Date& d1) const;
private:
    int month;
    int day;
    int year;
	tm formattedDate;
	time_t formmattedTime;

	
	void buildFormattedDate();
};

#endif /* Date_h */
