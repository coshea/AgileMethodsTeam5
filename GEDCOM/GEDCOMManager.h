//
//  IndividualManager.hpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef GEDCOMManager_h
#define GEDCOMManager_h

#include <stdio.h>
#include <map>
#include "Individual.h"
#include "Family.h"

using namespace std;

class GEDCOMManager
{
public:
    static GEDCOMManager* Instance();
    
    string addIndividual(string id, int currentLineNum, string errorFile);
    
    void addIndividual(string id, Individual i);
    
    Individual lookupIndividual(string id);
    
    void printIndividuals(string fileName);

	// US30 - List living Married
	void printLivingMarried(string fileName);

	// US31 - List living Single
	void printLivingSingle(string fileName);
    
    string addFamily(string id, int currentLineNum, string errorFile);
    
    void addFamily(string id, Family f);
    
    Family lookupFamily(string id);
    
	void addHusbandToFamily(string husbID, string famID);
    
	void addWifeToFamily(string wifeID, string famID);
    
    void printFamilies(string fileName);

	void errorCheck(string fileName);

	enum IDType 
	{
		FAMILY,
		INDIVIDUAL
	};
    
private:
    
    GEDCOMManager(){};  // Private so that it can  not be called
    GEDCOMManager(GEDCOMManager const&){};             // copy constructor is private
    static GEDCOMManager* m_pInstance;
};

#endif /* IndividualManager_h */
