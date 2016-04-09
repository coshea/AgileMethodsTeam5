//
//  Date.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "Date.h"
#include <sstream>
#include <time.h>

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

// contructor
//US41 - Include partial dates
//Accept and use dates without days or without days and months
Date::Date(string GEDCOMline)
{
	// Split string into vector
	vector<string> tokenizedLine;
	tokenize(GEDCOMline, tokenizedLine);

	// Line has day, month, year
	if(tokenizedLine.size() == 5)
	{
		day = stoi(tokenizedLine[2]);
		month = stringToMonth(tokenizedLine[3]);		
		year = stoi(tokenizedLine[4]);
	}
	// Line has month, year
	else if (tokenizedLine.size() == 4)
	{
		day = 1;
		month = stringToMonth(tokenizedLine[2]);
		year = stoi(tokenizedLine[3]);
	}
	// Line has year
	else if (tokenizedLine.size() == 3)
	{
		day = 1;
		month = 1;
		year = stoi(tokenizedLine[2]);
	}
	// Line is not valid
	else
	{
		day = 0;
		month = 0;
		year = 0;
	}



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
    switch (m)
    {
        case 1:
			return "JAN";
        case 2:
			return "FEB";
        case 3:
			return "MAR";
        case 4:
			return "APR";
        case 5:
			return "MAY";
        case 6:
			return "JUN";
        case 7:
			return "JUL";
        case 8:
			return "AUG";
        case 9:
			return "SEP";
        case 10:
			return "OCT";
        case 11:
			return "NOV";
        case 12:
			return "DEC";
		default:
			return "JAN";
    }
};

int Date::stringToMonth(string m)
{
	if (m == "JAN")
		return 1;
	if (m == "FEB")
		return 2;
	if (m == "MAR")
		return 3;
	if (m == "APR")
		return 4;
	if (m == "MAY")
		return 5;
	if (m == "JUN")
		return 6;
	if (m == "JUL")
		return 7;
	if (m == "AUG")
		return 8;
	if (m == "SEP")
		return 9;
	if (m == "OCT")
		return 10;
	if (m == "NOV")
		return 11;
	if (m == "DEC")
		return 12;
	return 1;
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

// Function to split string into a vector based on whitespace
void Date::tokenize(string input, vector<string>& output)
{
	string token;
	for (unsigned int i = 0; i <= input.size(); i++)
	{
		if (isspace(input[i]) || i == input.size())
		{
			output.push_back(token);
			token = "";
		}
		else
		{
			token += input[i];
		}
	}
};