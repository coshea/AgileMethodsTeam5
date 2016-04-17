//
//  IndividualManager.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "GEDCOMManager.h"
#include <fstream>
#include "Errors.h"

GEDCOMManager* GEDCOMManager::m_pInstance = NULL;

static map<string, Individual> individuals;
static map<string, Family> families;

// Husband/Wife ID, Married Date, Divorce Date
static map< string, vector<pair<Date, Date>>> myMarriage;

GEDCOMManager* GEDCOMManager::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
    {
        m_pInstance = new GEDCOMManager;
    }
    
    return m_pInstance;
}


string GEDCOMManager::addIndividual(string id, int currentLineNum, string errorFile)
{
	for (map<string, Individual>::iterator i = individuals.begin(); i != individuals.end(); i++)
	{
		if (i->first == id)
		{
			int firstLineNum = lookupIndividual(i->first).getLineNumber();
			id = CorrectRepeatedID(id, currentLineNum, firstLineNum, errorFile);
		}
	}
	individuals[id] = *new Individual;

	return id;
}

void GEDCOMManager::addIndividual(string id, Individual i)
{
    individuals[id] = i;
}

Individual GEDCOMManager::lookupIndividual(string id)
{
    return individuals.find(id)->second;
}

void GEDCOMManager::printIndividuals(string fileName)
{
    string outputFileName = "individuals" + string(fileName);
    ofstream outputStream(outputFileName);
    for(map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
    {
        outputStream << i->first << " " << i->second.getName() << "\n";
    }
    outputStream.close();
}

void GEDCOMManager::printDeceased(string fileName)
{
	string outputFileName = "deceased" + string(fileName);
	ofstream outputStream(outputFileName);
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (i->second.isDead())
		{
			outputStream << i->first << " " << i->second.getName() << "\n";
		}
	}
	outputStream.close();
}

void GEDCOMManager::printLivingMarried(string fileName)
{
	string outputFileName = "livingMarried" + string(fileName);
	ofstream outputStream(outputFileName);
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (!i->second.isDead() && i->second.getFAMS() != "")
		{
			outputStream << i->first << " " << i->second.getName() << "\n";
		}
	}
	outputStream.close();
}

void GEDCOMManager::printMultipleBirths(string fileName)
{
	string outputFileName = "multipleBirths" + string(fileName);
	ofstream outputStream(outputFileName);
	
	map<Date, vector<string> > birthdayToChild;

	for (map<string, Family >::iterator i = families.begin(); i != families.end(); ++i)
	{
		vector<string> children = i->second.getChildren();

		// Build map of birthdays to children
		for each (string id in children)
		{
			Date bday = lookupIndividual(id).getBirth();
			string name = lookupIndividual(id).getName();
			if (birthdayToChild.find(bday) == birthdayToChild.end())
			{
				vector<string> names;
				names.push_back(name);
				birthdayToChild[bday] = names;
			}
			else
			{
				vector<string> names(birthdayToChild[bday]);
				names.push_back(name);
				birthdayToChild[bday] = names;
			}
		}
	}

	// Loop over map and output to file
	for (map<Date, vector<string> >::iterator j = birthdayToChild.begin(); j != birthdayToChild.end(); ++j)
	{
		if (j->second.size() > 1)
		{
			outputStream << ((Date)j->first).toString() << "\n";

			vector<string> names(j->second);
			for each (string name in names)
			{
				outputStream << "\t" << name << "\n";
			}

			
		}
	}

	outputStream.close();
}

void GEDCOMManager::printOrphans(string fileName)
{
	string outputFileName = "orphans" + string(fileName);
	ofstream outputStream(outputFileName);
	for (map<string, Family >::iterator i = families.begin(); i != families.end(); ++i)
	{
		string wife = i->second.getWife();
		string husband = i->second.getHusband();

		if (lookupIndividual(wife).isDead() && lookupIndividual(husband).isDead())
		{
			vector<string> children = i->second.getChildren();
			for (size_t x = 0; x < children.size(); x++)
			{
				if (lookupIndividual(children[x]).getAge() < 18)
				{
					outputStream << children[x] << " " << lookupIndividual(children[x]).getName() << "\n";
				}
			}
		}
	}
	outputStream.close();
}

void GEDCOMManager::printLivingSingle(string fileName)
{
	string outputFileName = "livingSingle" + string(fileName);
	ofstream outputStream(outputFileName);
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (!i->second.isDead() && i->second.getFAMS() == "")
		{
			outputStream << i->first << " " << i->second.getName() << "\n";
		}
	}
	outputStream.close();
}

string GEDCOMManager::addFamily(string id, int currentLineNum, string errorFile)
{
	for (map<string, Family>::iterator i = families.begin(); i != families.end(); i++)
	{
		if (i->first == id)
		{
			Family f = lookupFamily(i->first);
			int firstLineNum = f.getLineNumber();
			id = CorrectRepeatedID(id, currentLineNum, firstLineNum, errorFile);
		}
	}
    families[id] = *new Family;

	return id;
}

void GEDCOMManager::addFamily(string id, Family f)
{
    families[id] = f;
}

Family GEDCOMManager::lookupFamily(string id)
{
    return families.find(id)->second;
}

void GEDCOMManager::addHusbandToFamily(string husbID, string famID)
{
	families[famID].setHusband(husbID);
}

void GEDCOMManager::addWifeToFamily(string wifeID, string famID)
{
	families[famID].setWife(wifeID);
}

void GEDCOMManager::printFamilies(string fileName)
{
    string outputFileName = "families" + string(fileName);
    ofstream familyStream(outputFileName);
    for(map<string, Family >::iterator f = families.begin(); f != families.end(); ++f)
    {
        familyStream << f->first << "\n\t"
			<< "Husband: " << lookupIndividual(f->second.getHusband()).getName() << "\n\t"
			<< "Wife: " << lookupIndividual(f->second.getWife()).getName() << "\n";
    }
    familyStream.close();
}

//US36-37 list deceased within 30 days & surviving relatives
void GEDCOMManager::printRecentDeaths(string fileName, int numDaysAgo)
{
	Date daysAgo;
	Family fam;
	Individual wife, husband, selectedChild;
	vector<string> children;
	daysAgo.SetDateDaysAgo(numDaysAgo);
	string deathsFileName = "RecentDeaths" + string(fileName);
	string survivorsFileName = "RecentSurvivors" + string(fileName);
	ofstream deathStream(deathsFileName);
	ofstream survivorStream(survivorsFileName);

	for (map<string, Individual>::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (i->second.getDeath() > daysAgo)
		{
			deathStream << i->first << " " << i->second.getName() << endl;
			fam = lookupFamily(i->second.getFAMS());
			wife = lookupIndividual(fam.getWife());
			husband = lookupIndividual(fam.getHusband());

			if (!wife.isDead())
			{
				survivorStream << wife.getName() << 
					" survived the recent death of her husband "<< i->second.getName() << endl;
			}
			if (!husband.isDead())
			{
				survivorStream << husband.getName() << 
					" survived the recent death of his wife " << i->second.getName() << endl;
			}

			children = fam.getChildren();
			for each (string  child in children)
			{
				selectedChild = lookupIndividual(child);
				if (!selectedChild.isDead())
				{
					if (selectedChild.getSex() == "M")
					{
						survivorStream << selectedChild.getName() <<
							" survived the recent death of his parent " << i->second.getName() << endl;
					}
					else
					{
						survivorStream << selectedChild.getName() <<
							" survived the recent death of her parent " << i->second.getName() << endl;
					}
				}
			}
		}
	}

	deathStream.close();
	survivorStream.close();
}

//US35 print biths within 30 days
void GEDCOMManager::printRecentBirths(string fileName, int numDaysAgo)
{
	Date daysAgo;
	daysAgo.SetDateDaysAgo(numDaysAgo);
	string outputFileName = "RecentBirths" + string(fileName);
	ofstream birthsStream(outputFileName);

	for (map<string, Individual>::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (i->second.getBirth() > daysAgo)
		{
			birthsStream << i->first << " " << i->second.getName() << endl;
		}
	}

	birthsStream.close();
}

void GEDCOMManager::buildIndividualMarriages(void)
{
	for (map<string, Family>::iterator f = families.begin(); f != families.end(); ++f)
	{
		    // map the Husbands
		    if (myMarriage.find(f->second.getHusband()) == myMarriage.end())
			{
				vector<pair<Date, Date>> mDates;
				mDates.push_back(make_pair(f->second.getMarried(),f->second.getDivorced()));
				myMarriage[f->second.getHusband()] = mDates;
			}
			else
			{
				vector<pair<Date, Date>> mDates(myMarriage[f->second.getHusband()]);
				mDates.push_back(make_pair(f->second.getMarried(), f->second.getDivorced()));
				myMarriage[f->second.getHusband()] = mDates;
			}

			// map the Wives
			if (myMarriage.find(f->second.getWife()) == myMarriage.end())
			{
				vector<pair<Date, Date>> mDates;
				mDates.push_back(make_pair(f->second.getMarried(), f->second.getDivorced()));
				myMarriage[f->second.getWife()] = mDates;
			}
			else
			{
				vector<pair<Date, Date>> mDates(myMarriage[f->second.getWife()]);
				mDates.push_back(make_pair(f->second.getMarried(), f->second.getDivorced()));
				myMarriage[f->second.getWife()] = mDates;
			}
	}
}

void GEDCOMManager::errorCheck(string fileName)
{	
	// Individual errors
	for (map<string, Individual>::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (i->second.getFAMS() != "")
		{
			// US02
			BirthBeforeMarriage(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));
			// US04
			MarriageBeforeDivorce(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));
			// US05
			MarriageBeforeDeath(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));
			// US06
			DivorceBeforeDeath(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));
			// US10
			MarriageBefore14(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));			
		}
		// US03
		BirthBeforeDeath(fileName, i->first, i->second);

		//US01, US07, US42
		IsDateValid(fileName, i->first, i->second);
	}

	// Family errors
	for (map<string, Family>::iterator i = families.begin(); i != families.end(); i++)
	{
		//US21
		CorrectGender(fileName, i->first);

		//US08
		ChildsBirthBeforeMarriageAndDivorce(fileName, i->second);

		//US09
		ChildsBirthBeforeParentsDeath(fileName, i->second);

		//US12
		ParentsNotTooOld(fileName, i->second);

		//US13
		SiblingSpacing(fileName, i->second);

		//US14
		MoreThan5Births(fileName, i->second);

		//US15
		MoreThan15Siblings(fileName, i->second);

		//US16
		MaleLastNames(fileName, i->second);

		for (map<string, Family>::iterator f = families.begin(); f != families.end(); f++)
		{
			//US17
			NoMarriageToChild(fileName, i->second, f->second);

			//US18	
			NoMarriageToSibling(fileName, i->second, f->second);
		}

		//US20
		AuntsUnclesNiecesNephews(fileName, i->second);
	}

	// Marriage errors
	for (map< string, vector<pair<Date, Date>>>::iterator m = myMarriage.begin(); m != myMarriage.end(); m++)
	{
		//US11
		NoBigamy(fileName, m->first, m->second);
	}
}

void GEDCOMManager::addAuntsAndUnclesToFamilies(void)
{
	vector<string> children, siblings;
	Individual husband, wife, tempInd;
	string sex;

	//first add siblings for each individual
	for (map<string, Family>::iterator i = families.begin(); i != families.end(); i++)
	{
		children = i->second.getChildren();
		if (children.size() > 1)
		{
			for each (string child in children)
			{
				for each (string sibling in children)
				{
					if (sibling != child)
					{
						tempInd = lookupIndividual(child);
						tempInd.addSibling(sibling);
						addIndividual(child, tempInd);
					}
				}
			}
		}
	}

	//then add the aunts and uncles to each family
	for (map<string, Family>::iterator i = families.begin(); i != families.end(); i++)
	{
		husband = lookupIndividual(i->second.getHusband());

		siblings = husband.getSiblings();

		if (siblings.size() >= 1)
		{
			for each(string sibling in siblings)
			{
				sex = lookupIndividual(sibling).getSex();

				if (sex == "M")
				{
					i->second.addUncle(sibling);
				}
				else if (sex == "F")
				{
					i->second.addAunt(sibling);
				}
				addFamily(i->first, i->second);
			}
		}

		wife = lookupIndividual(i->second.getWife());

		siblings = wife.getSiblings();

		if (siblings.size() >= 1)
		{
			for each(string sibling in siblings)
			{
				sex = lookupIndividual(sibling).getSex();

				if (sex == "M")
				{
					i->second.addUncle(sibling);
				}
				else if (sex == "F")
				{
					i->second.addAunt(sibling);
				}
				addFamily(i->first, i->second);
			}
		}
	}
}