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


void IsDateValid(string fileName, string first, Individual &i)
{
	Logger errorLog(fileName);
	Date birth = i.getBirth();
	Date death = i.getDeath();
	int lineNum = i.getLineNumber();
	string name = i.getName();

	//US42 - Reject illegitimate dates
	if (!birth.isDateValid())
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US42: Birth date of " << name <<
			" (" << first << ") is not a valid date." << "\n";
	}

	//US42 - Reject illegitimate dates
	if (i.isDead() && !death.isDateValid())
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US42: Death date of " << name <<
			" (" << first << ") is not a valid date." << "\n";
	}

	//US01 - Dates before current date
	if (!birth.isInPast())
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US01: Birth date of " << name <<
			" (" << first << ") is not in the past." << "\n";
	}

	//US01 - Dates before current date
	if (i.isDead() && !death.isDateValid())
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US01: Death date of " << name <<
			" (" << first << ") is not in the past." << "\n";
	}
	

	//US07 - Less then 150 years old
	//Death should be less than 150 years after birth for dead people
	//current date should be less than 150 years after birth for all living people
	if (i.getAge() > 150)
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US07: " << name <<
			" (" << first << ") is over 150 years old." << "\n";
	}
}

// US21
void CorrectGender(string fileName, string familyID)
{
	Family fam;
	Individual husband, wife;
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	fam = manager->lookupFamily(familyID);
	husband = manager->lookupIndividual(fam.getHusband());
	wife = manager->lookupIndividual(fam.getWife());

	if (husband.getSex() != "M")
	{
		errorLog(LogLevel::ERROR, husband.getLineNumber()) <<
			"Husband from family (" << familyID << ") is not a male." << "\n";
	}

	if (wife.getSex() != "F")
	{
		errorLog(LogLevel::ERROR, wife.getLineNumber()) <<
			"Wife from family (" << familyID << ") is not a female." << "\n";
	}
}