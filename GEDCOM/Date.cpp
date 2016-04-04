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

int Date::getMonth()
{
    return month;
};


int Date::getDay()
{
    return day;
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

		if (day == 29 && !isLeapYear())
			return false;
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

int Date::getEndOfMonthDay()
{
	switch(month)
	{
		case 4: case 6: case 9: case 11:
			return 30;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 2:
		{
			if (isLeapYear())
				return 29;
			else
				return 28;
		}
		default:
			return 0;
	}
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

bool Date::isLeapYear()
{
	if (year % 4 != 0)
		return false;
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	return true;
}

void Date::AddDays(int number)
{
	if(number > 0)
	{
		// If months don't need to change
		if (number + day <= getEndOfMonthDay())
		{
			day += number;
		}
		else
		{
			while (number != 0)
			{
				if (day + 1 > getEndOfMonthDay())
				{
					AddMonths(1);
					day = 1;
				}
				else
				{
					day++;
				}
				number--;
			}
		}
	}
	else
	{
		// If months don't need to change
		if (number + day > 0)
		{
			day += number;
		}
		else
		{
			while (number != 0)
			{
				if (day - 1 == 0)
				{
					AddMonths(-1);
					day = getEndOfMonthDay();
				}
				else
				{
					day--;
				}
				number++;
			}
		}
	}
	
	buildFormattedDate();
}

void Date::AddMonths(int number)
{
	if(month + number > 12)
	{
		year++;
		month = month + number - 12;
	}
	else if(month + number < 1)
	{
		year--;
		month = 12 + month + number;
	}
	else
	{
		month += number;
	}

	// Set new date to end of month if needed
	if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
	{
		day = 30;
	}
	else if(month == 2 && day > 28)
	{
		if (isLeapYear())
			day = 29;
		else
			day = 28;
	}

	buildFormattedDate();
}

void Date::AddYears(int number)
{
	year += number;

	// Move date to 3/1 if new date is not a leap year but old date was on leap day
	if(day == 29 && month == 2 && !isLeapYear())
	{
		day = 1;
		month = 3;
	}

	buildFormattedDate();
}

bool Date::operator==(const Date & d1) const
{
	if (this->year == d1.year 
		&& this->month == d1.month 
		&& this->day == d1.day)
		return true;
	return false;
}

bool Date::operator>(const Date & d1) const
{
	bool retVal = false;

	if (d1.year == 0)
		return retVal;

	if (d1.year < this->year)
	{
		retVal = true;
	}
	else if ((d1.year == this->year) &&
		(d1.month < this->month))
	{
		retVal = true;
	}
	else if ((d1.year == this->year) &&
		(d1.month == this->month) &&
		(d1.day < this->day))
	{
		retVal = true;
	}

	return retVal;
}

bool Date::operator<(const Date & d1) const
{
	bool retVal = false;

	if (d1.year == 0)
		return retVal;

	if (d1.year > this->year)
	{
		retVal = true;
	}
	else if ((d1.year == this->year) &&
		(d1.month > this->month))
	{
		retVal = true;
	}
	else if ((d1.year == this->year) &&
		(d1.month == this->month) &&
		(d1.day > this->day))
	{
		retVal = true;
	}

	return retVal;
}

//US35-37 sets the date to numDays ago 
void Date::SetDateDaysAgo(int numDays)
{
	time_t currentTime = time(0);//time expressed in seconds
	time_t newTime = currentTime - (numDays * 60 * 60 * 24);
	tm* newDate = localtime(&newTime);

	//account for the formatting of the tm struct
	year = (newDate->tm_year + 1900);
	month = (newDate->tm_mon + 1);
	day = newDate->tm_mday;

	buildFormattedDate();
}