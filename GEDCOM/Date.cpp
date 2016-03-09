//
//  Date.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "Date.h"

Date::Date()
{
    month = 0;
    day = 0;
    year = 0;
	buildFormattedDate();
}

// contructor
Date::Date(int d, int m, int y)
{
    month = m;
    day = d;
    year = y;
	buildFormattedDate();
};

// contructor
Date::Date(string d, string m, string y)
{
	month = stringToMonth(m);
	day = stoi(d);
	year = stoi(y);
	buildFormattedDate();
};

void Date::setMonth(int m)
{
    month = m;
};

int Date::getMonth()
{
    return month;
};

void Date::setDay(int d)
{
    day = d;
};

int Date::getDay()
{
    return day;
};

void Date::setYear(int y)
{
    year = y;
};

int Date::getYear()
{
    return year;
};

string Date::toString()
{
    stringstream date;
    date << monthToString(month) << " " << day << " " << year;
    return date.str();
};

string Date::monthToString(int m)
{
    string ret;
    switch (m)
    {
        case 1:
            ret = "JAN";
        case 2:
            ret = "FEB";
        case 3:
            ret = "MAR";
        case 4:
            ret = "APR";
        case 5:
            ret = "MAY";
        case 6:
            ret = "JUN";
        case 7:
            ret = "JUL";
        case 8:
            ret = "AUG";
        case 9:
            ret = "SEP";
        case 10:
            ret = "OCT";
        case 11:
            ret = "NOV";
        case 12:
            ret = "DEC";
    }
    return ret;
};

int Date::stringToMonth(string m)
{
	int ret;
	if (m == "JAN")
		ret = 1;
	if (m == "FEB")
		ret = 2;
	if (m == "MAR")
		ret = 3;
	if (m == "APR")
		ret = 4;
	if (m == "MAY")
		ret = 5;
	if (m == "JUN")
		ret = 6;
	if (m == "JUL")
		ret = 7;
	if (m == "AUG")
		ret = 8;
	if (m == "SEP")
		ret = 9;
	if (m == "OCT")
		ret = 10;
	if (m == "NOV")
		ret = 11;
	if (m == "DEC")
		ret = 12;

	return ret;
};




//US42 Reject illegitimate dates
//All dates should be legitimate dates for the months specified
bool Date::isDateValid()
{
	if (month < 1 || month > 12)
		return false;

	if (day < 1 || day > 31)
		return false;

	if (day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
		return false;

	if (month == 2)
	{
		if (day > 29)
			return false;

		if (day == 29)
		{
			if (year % 4 != 0)
				return false;
			if (year % 400 == 0)
				return true;
			if (year % 100 == 0)
				return false;
		}
	}
	return true;
};

//US01 Dates before current date
//Dates (birth, marriage, divorce, death) should not be after the current date
bool Date::isInPast()  
{
	time_t currentTime = time(0);

	if (formmattedTime < currentTime)
		return true;
	else
		return false;
};

void Date::buildFormattedDate()
{
	formattedDate = { 0 };
	formattedDate.tm_mon = month - 1;
	formattedDate.tm_mday = day;
	formattedDate.tm_year = year - 1900;
	formattedDate.tm_hour = 0;
	formattedDate.tm_min = 0;
	formattedDate.tm_sec = 0;

	formmattedTime = mktime(&formattedDate);
}

bool Date::occursAfter(Date target)
{
	bool retVal = false;

	if (target.getYear() == 0)
		return retVal;

	if (target.getYear() < year)
	{
		retVal = true;
	}
	else if ((target.getYear() == year) &&
		(target.getMonth() < month))
	{
		retVal = true;
	}
	else if ((target.getYear() == year) &&
		(target.getMonth() == month) &&
		(target.getDay() < day))
	{
		retVal = true;
	}

	return retVal;
}