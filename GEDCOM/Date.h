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
#include <vector>


using namespace std;
//using namespace Utilities;

class Date
{
public:
    
	Date();
    
    // contructor
	Date(int d, int m, int y);

	// contructor
	Date(string d, string m, string y);

	// contructor
	Date(string GEDCOMline);
        
    int getMonth();
        
    int getDay();
        
    int getYear();
    
    string toString();
    
    string monthToString(int m);

	int stringToMonth(string m);

	bool isInPast();

	bool isDateValid();

	bool occursAfter(Date target);

	bool isLeapYear();

	void AddDays(int number);

	void AddMonths(int number);

	void AddYears(int number);

	int getEndOfMonthDay();

	void SetDateDaysAgo(int numDays);

	bool operator==(const Date& d1) const;
	bool operator>(const Date& d1) const;
	bool operator<(const Date& d1) const;

	// Convert to Epoch plus 200 years to get around time_t problems with dates before epoch
	time_t sinceEpochPlus200();

private:
    int month;
    int day;
    int year;
	tm formattedDate;
	time_t formmattedTime;

	void tokenize(string input, vector<string>& output);
	void buildFormattedDate();
};

#endif /* Date_h */
