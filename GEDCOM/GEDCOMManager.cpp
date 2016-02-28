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


void GEDCOMManager::addIndividual(string id)
{
    individuals[id] = *new Individual;
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

void GEDCOMManager::addFamily(string id)
{
    families[id] = *new Family;
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
    Family f = families.find(famID)->second;
    f.setHusband(husbID);
    families[famID] = f;
}

void GEDCOMManager::addWifeToFamily(string wifeID, string famID)
{
    Family f = families.find(famID)->second;
    f.setWife(wifeID);
    families[famID] = f;
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
	for (map<string, Individual >::iterator i = individuals.begin(); i != individuals.end(); ++i)
	{
		if (i->second.getFAMS() != "")
		{
			// US02
			BirthBeforeMarriage(fileName, i->first, i->second, lookupFamily(i->second.getFAMS()));
		}
		// US03
		BirthBeforeDeath(fileName, i->first, i->second);

		//US01, US07, US42
		IsDateValid(fileName, i->first, i->second);
	}
}
