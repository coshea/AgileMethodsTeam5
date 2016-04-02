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
#include "Errors.h"

// US03 - check that birth occurs before death
void BirthBeforeDeath(string fileName, string first, Individual &i)
{
	Date  birth = i.getBirth();
	Date  death = i.getDeath();
	string name = i.getName();
	string sex  = i.getSex();
	int lineNum = i.getLineNumber();

	if (birth.occursAfter(death))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";
			
		errorLog(LogLevel::ERROR, lineNum) << 
		    "US03: Birth date of " << name << " (" << first << 
			") occurs after " << pronoun << " death date." << "\n";
	}
}

// US02 - check that birth occurs before marriage
void BirthBeforeMarriage(string fileName, string first, Individual &i, Family &f)
{
	Date  birth   = i.getBirth();
	Date  married = f.getMarried();
	string name   = i.getName();
	string sex    = i.getSex();
	int lineNum   = i.getLineNumber();

	if (birth.occursAfter(married))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";

		errorLog(LogLevel::ERROR, lineNum) <<
			"US02: Birth date of " << name << " (" << first <<
			") occurs after " << pronoun << " marriage date." << "\n";
	}
}

// US04 - check that marriage occurs before divorce
void MarriageBeforeDivorce(string fileName, string first, Individual &i, Family &f)
{
	Date  married = f.getMarried();
	Date  divorce = f.getDivorced();
	string name   = i.getName();
	string sex    = i.getSex();
	int lineNum   = i.getLineNumber();

	if (married.occursAfter(divorce))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";

		errorLog(LogLevel::ERROR, lineNum) <<
			"US04: Marriage date of " << name << " (" << first <<
			") occurs after " << pronoun << " divorce date." << "\n";
	}
}

// US05 - check that marriage occurs before death
void MarriageBeforeDeath(string fileName, string first, Individual &i, Family &f)
{
	Date  death   = i.getDeath();
	Date  married = f.getMarried();
	string name   = i.getName();
	string sex    = i.getSex();
	int lineNum   = i.getLineNumber();

	if (married.occursAfter(death))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";

		errorLog(LogLevel::ERROR, lineNum) <<
			"US05: Marriage date of " << name << " (" << first <<
			") occurs after " << pronoun << " death date." << "\n";
	}
}

// US06 - check that divorce occurs before death
void DivorceBeforeDeath(string fileName, string first, Individual &i, Family &f)
{
	Date  death    = i.getDeath();
	Date  divorced = f.getDivorced();
	string name    = i.getName();
	string sex     = i.getSex();
	int lineNum    = i.getLineNumber();

	if (divorced.occursAfter(death))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";

		errorLog(LogLevel::ERROR, lineNum) <<
			"US06: Divorce date of " << name << " (" << first <<
			") occurs after " << pronoun << " death date." << "\n";
	}
}

//US42 - Reject illegitimate dates
//US01 - Dates before current date
//US07 - Less then 150 years old
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

// US21 - Correct gender for role
//Husband in family should be male and wife in family should be female
void CorrectGender(string fileName, string familyID)
{
	Family fam;
	Individual husband, wife;
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	fam = manager->lookupFamily(familyID);
	husband = manager->lookupIndividual(fam.getHusband());
	wife = manager->lookupIndividual(fam.getWife());
	vector<string> children = fam.getChildren();
	if (husband.getSex() != "M")
	{
		errorLog(LogLevel::ERROR, husband.getLineNumber()) <<
			"US21: Husband from family (" << familyID << ") is not a male." << "\n";
	}

	if (wife.getSex() != "F")
	{
		errorLog(LogLevel::ERROR, wife.getLineNumber()) <<
			"US21: Wife from family (" << familyID << ") is not a female." << "\n";
	}
}

//US 22 - Unique IDs
//All individual IDs should be unique and all family IDs should be unique
string CorrectRepeatedID(string id, int currentLineNum, int firstLineNum, string fileName)
{
	Logger errorLog(fileName);
	string newID = id + "_" + to_string(currentLineNum);

	errorLog(LogLevel::ERROR, currentLineNum) << "US22: " <<
		id << " is repeated on line " << 
		firstLineNum << " and " << currentLineNum << ".\n";
	errorLog(LogLevel::INFO, currentLineNum) << "US22: " <<
		id << " at line " << currentLineNum <<
		" has been changed to " << newID << " to maintain unique IDs.\n";

	return newID;
}

//US08 - Birth before marriage of parents
//Child should be born after marriage of parents (and before their divorce)
void ChildsBirthBeforeMarriageAndDivorce(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	Date married = f.getMarried();
	Date divorced = f.getDivorced();

	for each (string Id in children)
	{
		Individual child = manager->lookupIndividual(Id);
		Date childBorn = child.getBirth();
		int lineNum = child.getLineNumber();
		string name = child.getName();

		if (childBorn < married)
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US08: Birth date of " << name <<
				" (" << Id << ") is before parents marriage."<< "\n";
		}

		if (childBorn > divorced)
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US08: Birth date of " << name <<
				" (" << Id << ") is after parents divorce." << "\n";
		}
	}
}

//US09
//Child should be born before death of mother 
//and before 9 months after death of father
void ChildsBirthBeforeParentsDeath(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	string motherId = f.getWife();
	string fatherId = f.getHusband();

	Individual mother = manager->lookupIndividual(motherId);
	Individual father = manager->lookupIndividual(fatherId);

	for each (string Id in children)
	{
		Individual child = manager->lookupIndividual(Id);
		Date childBorn = child.getBirth();
		Date conception = child.getBirth();
		conception.AddMonths(-9);

		int lineNum = child.getLineNumber();
		string name = child.getName();

		//Child should be born before death of mother 
		if (childBorn > mother.getDeath())
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US09: Birth date of " << name <<
				" (" << Id << ") is after mother died." << "\n";
		}
		
		//and before 9 months after death of father
		if (conception > father.getDeath())
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US09: Birth date of " << name <<
				" (" << Id << ") is greater than 9 months after father died." << "\n";
		}
	}

}

//US12 - Parents not too old
//Mother should be less than 60 years older than her children 
//Father should be less than 80 years older than his children
void ParentsNotTooOld(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	string motherId = f.getWife();
	string fatherId = f.getHusband();

	Individual mother = manager->lookupIndividual(motherId);
	Individual father = manager->lookupIndividual(fatherId);
	Date acceptableChildDateForMother = mother.getBirth();
	Date acceptableChildDateForFather = father.getBirth();

	// Calculate max acceptable dates for child to be born
	acceptableChildDateForMother.AddYears(60);
	acceptableChildDateForFather.AddYears(80);

	string motherName = mother.getName();
	string fatherName = father.getName();

	for each (string Id in children)
	{
		Individual child = manager->lookupIndividual(Id);
		Date childBorn = child.getBirth();
		int lineNum = child.getLineNumber();
		string childName = child.getName();

		//Child should be born before acceptable date for mother
		if (childBorn > acceptableChildDateForMother)
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US12: " << motherName << " (" << Id 
				<< ") is over 60 years older than child "
				<< childName << " (" << Id << " )\n";
		}

		//Child should be born before acceptable date for father
		if (childBorn > acceptableChildDateForFather)
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US12: " << fatherName << " (" << Id
				<< ") is over 80 years older than child "
				<< childName << " (" << Id << " )\n";
		}
	}
}
