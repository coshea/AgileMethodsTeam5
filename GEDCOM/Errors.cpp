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
#include <algorithm>

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

// US10	- check that marriage occurs after 14	
// Marriage should be at least 14 years after birth
void MarriageBefore14(string fileName, string first, Individual &i, Family &f)
{
	Date  birth14th = i.getBirth();
	birth14th.AddYears(14);
	Date  married = f.getMarried();
	string name = i.getName();
	string sex = i.getSex();
	int lineNum = i.getLineNumber();

	if (birth14th.occursAfter(married))
	{
		Logger errorLog(fileName);
		string pronoun = "her";

		if (sex != "F")
			pronoun = "his";

		errorLog(LogLevel::ERROR, lineNum) <<
			"US10: Marriage date of " << name << " (" << first <<
			") occurs before " << pronoun << " 14th birthday." << "\n";
	}
}

// US11	- No Bigamy
// Marriage should not occur during marriage to another spouse
void NoBigamy(string fileName, string id, vector<pair<Date, Date>> m)
{
	if (m.size() > 1)
	{ // there was more than one marriage
		bool error = false;
		Logger errorLog(fileName);
		GEDCOMManager * manager = GEDCOMManager::Instance();
		// check for overlaps
		for (vector<pair<Date, Date>>::iterator one = m.begin(); one != m.end(); ++one)
		{
			for (vector<pair<Date, Date>>::iterator two = m.begin(); two != m.end(); ++two)
			{
				if (one != two) // don't check the same
				{
					if ((!one->second.isDateValid()) && // no divorce
						(!two->second.isDateValid()))
					{
						error = true;
					}

					// compare the marriage dates
					if (one->first > two->first)  // greater than is 2000 > 1969					
					{
						if (!two->second.isDateValid())  // older marriage no divorce
						{
							error = true;
						}
						else if (two->second > one->first)  // divorce after new marriage
						{
							error = true;
						}
					}
					else // less than or equal					
					{
						if (!one->second.isDateValid())  // older marriage no divorce
						{
							error = true;
						}
						else if (one->second > two->first)  // divorce after new marriage
						{
							error = true;
						}
					}
				}
			}
		}
		if (error)
		{
			Individual person = manager->lookupIndividual(id);
			int lineNum = person.getLineNumber();
			string name = person.getName();

			errorLog(LogLevel::ERROR, lineNum) <<
				"US11: Marriage of " << name << " (" << id <<
				") resulted in Bigamy." << "\n";
		}
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

//US13 - Siblings spacing
//Birth dates of siblings should be more than 8 months apart or less than 2 days apart
void SiblingSpacing(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	std::vector<string>::iterator it;

	for (size_t n = 1; n < children.size(); ++n)
	{
		Individual child1 = manager->lookupIndividual(children[n]);
		Individual child2 = manager->lookupIndividual(children[n-1]);

		Date child1Born = child1.getBirth();
		Date child2Born = child2.getBirth();
		
		Date youngerChild;
		Date olderChild;

		if(child1Born < child2Born)
		{
			youngerChild = child1.getBirth();
			olderChild = child2.getBirth();
		}
		else
		{
			youngerChild = child2.getBirth();
			olderChild = child1.getBirth();
		}

		Date EightMonthsOlder  = youngerChild;
		Date TwoDaysOlder = youngerChild;
		EightMonthsOlder.AddMonths(8);
		TwoDaysOlder.AddDays(2);

		if (olderChild > EightMonthsOlder || olderChild < TwoDaysOlder)
		{
			continue;
		}
		
		int child1lineNum = child1.getLineNumber();
		string child1Name = child1.getName();
		int child2lineNum = child2.getLineNumber();
		string child2Name = child2.getName();

		//Older child is born more than 2 days apart but less than 8 months apart
		errorLog(LogLevel::ERROR, child1lineNum) <<
			"US13: Birth dates of " << child1Name <<
			" (" << children[n] << ") and " << child2Name <<
			" (" << children[n-1] << ") are more than 2 days apart but less than 8 months apart." << "\n";
		errorLog(LogLevel::ERROR, child2lineNum) <<
			"US13: Birth dates of " << child2Name <<
			" (" << children[n - 1] << ") and " << child1Name <<
			" (" << children[n] << ") are more than 2 days apart but less than 8 months apart." << "\n";
	}

}

//US14 - Multiple births 5 or less
//No more than five siblings should be born at the same time
void MoreThan5Births(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();

	// check if there are more than 5 children
	if (children.size() > 5)
	{
		Individual child;
		Date checkBirth;
		Date childBorn;
		int count = 0;
		bool error = false;

		for each (string Id in children)
		{
			child = manager->lookupIndividual(Id);
			checkBirth = child.getBirth();
			count = 0;
			for each (string Id in children)
			{
				child = manager->lookupIndividual(Id);
				childBorn = child.getBirth();
				if (checkBirth == childBorn)
					count++;
			}
			if (count > 5)
				error = true;
		}
		if (error)
		{
			string motherId = f.getWife();
			Individual mother = manager->lookupIndividual(motherId);
			int lineNum = mother.getLineNumber();
			string motherName = mother.getName();

			errorLog(LogLevel::ERROR, lineNum) <<
				"US14: " << motherName << " (" << motherId <<
				") had multiple births more than 5.\n";
		}
	}
}

//US20 Aunts and Uncles should not marry Nieces and Nephews
void AuntsUnclesNiecesNephews(string fileName, Family &f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);
	vector<string> children, auntsUncles;
	string spouse, childsSex, fams;
	int lineNum;

	children = f.getChildren();

	if (children.size() >= 1)
	{
		for each(string child in children)
		{
			auntsUncles = f.getAunts();
			for each(string auntUncle in auntsUncles)
			{
				fams = manager->lookupIndividual(auntUncle).getFAMS();
				if (fams != "")
				{
					//spouse = manager->lookupFamily(spouse).getHusband();
				}
				if (spouse == child)
				{
					lineNum = manager->lookupIndividual(auntUncle).getLineNumber();
					childsSex = manager->lookupIndividual(child).getSex();
					if (childsSex == "M")
					{
						errorLog(LogLevel::ERROR, lineNum) <<
							"US20: " << auntUncle <<
							" Married her nephew " << child << endl;
					}
					else if (childsSex == "F")
					{
						errorLog(LogLevel::ERROR, lineNum) <<
							"US20: " << auntUncle <<
							" Married her niece " << child << endl;
					}
				}
			}
			auntsUncles = f.getUncles();
			for each(string auntUncle in auntsUncles)
			{
				fams = manager->lookupIndividual(auntUncle).getFAMS();
				if (fams != "")
				{
					//spouse = manager->lookupFamily(spouse).getWife();
				}
				if (spouse == child)
				{
					lineNum = manager->lookupIndividual(auntUncle).getLineNumber();
					childsSex = manager->lookupIndividual(child).getSex();
					if (childsSex == "M")
					{
						errorLog(LogLevel::ERROR, lineNum) <<
							"US20: " << auntUncle <<
							" Married his nephew " << child << endl;
					}
					else if (childsSex == "F")
					{
						errorLog(LogLevel::ERROR, lineNum) <<
							"US20: " << auntUncle <<
							" Married his niece " << child << endl;
					}
				}
			}
		}
	}
}


//US15 - Fewer than 15 siblings
//There should be fewer than 15 siblings in a family
void MoreThan15Siblings(string fileName, Family & f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	string familyName = f.getId();
	int lineNum = f.getLineNumber();

	// check if there are more than 14 children
	if (children.size() > 14)
	{
		errorLog(LogLevel::ERROR, lineNum) <<
			"US15: Family" << " (" << familyName <<
			") has more than 15 children.\n";
	}
}

//US16 - Male last names
//All male members of a family should have the same last name
void MaleLastNames(string fileName, Family& f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = f.getChildren();
	string fatherId = f.getHusband();

	Individual father = manager->lookupIndividual(fatherId);
	string fatherLastName = father.getLastName();

	for each (string Id in children)
	{
		Individual child = manager->lookupIndividual(Id);

		// only check male children
		if (child.getSex() != "M")
			continue;

		int lineNum = child.getLineNumber();
		string childName = child.getName();
		string childLastName = child.getLastName();

		//Male childs last name should match fathers name
		if (childLastName != fatherLastName)
		{
			errorLog(LogLevel::ERROR, lineNum) <<
				"US16: " << childName << " (" << Id
				<< ") last name does not match fathers name of "
				<< fatherLastName << " (" << fatherId << ")\n";
		}
	}

}

//US17 - No marriages to descendants
//Parents should not marry any of their descendants
void NoMarriageToChild(string fileName, Family& i, Family& f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	string fatherId = i.getHusband();
	Individual father = manager->lookupIndividual(fatherId);
	string motherId = i.getWife();
	Individual mother = manager->lookupIndividual(motherId);
	vector<string> children = i.getChildren();

	string husbandId = f.getHusband();
	string wifeId = f.getWife();

	for each (string childId in children)
	{
		if ((fatherId == husbandId) &&
			(wifeId == childId))
		{
			int lineNum = father.getLineNumber();
			string fatherName = father.getName();
			Individual child = manager->lookupIndividual(childId);
			string childName = child.getName();
			errorLog(LogLevel::ERROR, lineNum) <<
				"US17: " << fatherName << " (" << fatherId
				<< ") married his child " << childName << " (" << childId << ")\n";
		}

		if ((motherId == wifeId) &&
			(husbandId == childId))
		{
			int lineNum = mother.getLineNumber();
			string motherName = mother.getName();
			Individual child = manager->lookupIndividual(childId);
			string childName = child.getName();
			errorLog(LogLevel::ERROR, lineNum) <<
				"US17: " << motherName << " (" << motherId
				<< ") married her child " << childName << " (" << childId << ")\n";
		}
	}

}

//US18 - No marriages to siblings
//Siblings should not marry one another
void NoMarriageToSibling(string fileName, Family& i, Family& f)
{
	GEDCOMManager * manager = GEDCOMManager::Instance();
	Logger errorLog(fileName);

	vector<string> children = i.getChildren();

	string husbandId = f.getHusband();
	string wifeId = f.getWife();

	string hubbieId;
	string wifieId;

	for each (string childId in children)
	{
		hubbieId = "";
		wifieId = "";
		Individual firstChild = manager->lookupIndividual(childId);
		if (firstChild.getSex() != "F")
		{
			hubbieId = childId;
		}
		else // Sex == "F"
		{
			wifieId = childId;
		}

		for each (string childId in children)
		{
			Individual secondChild = manager->lookupIndividual(childId);
			if (secondChild.getSex() != "F")
			{
				if (hubbieId == "")
				{
					hubbieId = childId;
				}
			}
			else // Sex == "F"
			{
				if (wifieId == "")
				{
					wifieId = childId;
				}
			}
		}

		if ((husbandId == hubbieId) &&
			(wifeId == wifieId))
		{
			Individual husband = manager->lookupIndividual(husbandId);
			int lineNum = husband.getLineNumber();
			string husbandName = husband.getName();
			Individual wife = manager->lookupIndividual(wifeId);
			string wifeName = wife.getName();
			errorLog(LogLevel::ERROR, lineNum) <<
				"US18: " << husbandName << " (" << husbandId
				<< ") married his sibling " << wifeName << " (" << wifeId << ")\n";
		}
	}

}