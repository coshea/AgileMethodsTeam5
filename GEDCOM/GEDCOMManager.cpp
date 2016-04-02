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
    ofstream individualStream(outputFileName);
    for(map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
    {
        individualStream << i->first << " " << i->second.getName() << "\n";
    }
    individualStream.close();
}

void GEDCOMManager::printLivingMarried(string fileName)
{
	string outputFileName = "livingMarried" + string(fileName);
	ofstream individualStream(outputFileName);
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (!i->second.isDead() && i->second.getFAMS() != "")
		{
			individualStream << i->first << " " << i->second.getName() << "\n";
		}
	}
	individualStream.close();
}

void GEDCOMManager::printLivingSingle(string fileName)
{
	string outputFileName = "livingSingle" + string(fileName);
	ofstream individualStream(outputFileName);
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (!i->second.isDead() && i->second.getFAMS() == "")
		{
			individualStream << i->first << " " << i->second.getName() << "\n";
		}
	}
	individualStream.close();
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


void GEDCOMManager::errorCheck(string fileName)
{	
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
		}
		// US03
		BirthBeforeDeath(fileName, i->first, i->second);

		//US01, US07, US42
		IsDateValid(fileName, i->first, i->second);
	}

	// Then check for family errors
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
		
	}
}
