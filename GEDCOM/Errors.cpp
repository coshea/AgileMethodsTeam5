//
//  Errors.cpp
//  GEDCOM
//
//  Created by M. Scully on 2/21/16
//

#include "GEDCOMManager.h"
#include "Date.h"
#include "Family.h"
#include <fstream>
#include "Individual.h"
#include "Logger.h"

// US03 - check that birth occurs before death
void BirthBeforeDeath(string fileName, string first, Individual &i)
{
	Date  birth = i.getBirth();
	Date  death = i.getDeath();
	string name = i.getName();
	string sex = i.getSex();
	int lineNum = i.getLineNumber();

	bool error = false; 
	
	if (death.getYear() == 0) 
		return;

	if (death.getYear() < birth.getYear())
	{
		error = true;
	}
	else if ((death.getYear() == birth.getYear()) && 
		(death.getMonth() < birth.getMonth()))
	{
		error = true;
	}
	else if ((death.getYear() == birth.getYear()) &&
		(death.getMonth() == birth.getMonth()) &&
		(death.getDay() < birth.getDay()))
	{
		error = true;
	}

	if (error)
	{
		Logger errorLog(fileName);

		if (sex != "F")
		{
			errorLog(LogLevel::ERROR, lineNum) << 
				"US03: Birth date of " << name << 
				" (" << first << ") occurs after his death date." << "\n";
		}
		else
		{
			errorLog(LogLevel::ERROR, lineNum) << 
				"US03: Birth date of " << name << 
				" (" << first << ") occurs after her death date." << "\n";
		}
	}
}

// US02 - check that birth occurs before marriage
void BirthBeforeMarriage(string fileName, string first, Individual &i, Family &f)
{
	Date  birth = i.getBirth();
	Date  married = f.getMarried();

	string name = i.getName();
	string sex = i.getSex();
	int lineNum = i.getLineNumber();

	bool error = false;

	if (married.getYear() == 0)
		return;

	if (married.getYear() < birth.getYear())
	{
		error = true;
	}
	else if ((married.getYear() == birth.getYear()) &&
		(married.getMonth() < birth.getMonth()))
	{
		error = true;
	}
	else if ((married.getYear() == birth.getYear()) &&
		(married.getMonth() == birth.getMonth()) &&
		(married.getDay() < birth.getDay()))
	{
		error = true;
	}

	if (error)
	{
		Logger errorLog(fileName);
		if (sex != "F")
		{
			errorLog(LogLevel::ERROR, lineNum) << 
				"US02: Birth date of " << name << 
				" (" << first << ") occurs after his marriage date." << "\n";
		}
		else
		{
			errorLog(LogLevel::ERROR, lineNum) << 
				"US02: Birth date of " << name << 
				" (" << first << ") occurs after her marriage date." << "\n";
		}
	}
}
