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

using namespace std;

class Date
{
public:
    
    Date();
    
    // contructor
    Date(int d, int m, int y);
    
    void setMonth(int m);
    
    int getMonth();
    
    void setDay(int d);
    
    int getDay();
    
    void setYear(int y);
    
    int getYear();
    
    string toString();
    
    string monthToString(int m);

	int stringToMonth(string m);
    
private:
    int month;
    int day;
    int year;
};

#endif /* Date_h */
