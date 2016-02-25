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
}

// contructor
Date::Date(int d, int m, int y)
{
    month = m;
    day = d;
    year = y;
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