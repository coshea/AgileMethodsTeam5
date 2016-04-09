//
//  GEDCOM.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/6/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Date.h"
#include "GEDCOMManager.h"
#include "Individual.h"
#include "Family.h"
#include "Utilities.h"

// Main function
int main(int argc, const char * argv[])
{
    GEDCOMManager *manager = GEDCOMManager::Instance();
    
    // Input file
	string inputFileName;
#ifdef consoleApp
	cout << "Please enter name of GEDCOM file: ";
	cin >> inputFileName;
	cout << endl;
#else
	inputFileName = argv[1];
#endif
    // Input file
    ifstream gedcomFile(inputFileName);

    // Output file
    string outputFileName = "processed" + string(inputFileName);
	string errorFileName = "errors" + string(inputFileName);

    ofstream processedGEDCOM(outputFileName);
    
    // read lines from input file
    string line;
    string levelZeroID;
    string levelZeroTAG;
	string levelOneTAG = "";
	int lineNumber = 0;

    while (getline(gedcomFile, line))
    {
		lineNumber++;

        // Write line to output file
        processedGEDCOM << line << "\n";
        
        // Split string into vector
        vector<string> tokenizedLine;
        Utilities::tokenize(line, tokenizedLine);
        
        // Get level from first token
        int level = Utilities::getLevel(tokenizedLine);
        
        // Check if level is valid
        // Valid levels: 0 - 2
        if(level > -1 && level < 3)
        {
            processedGEDCOM  << level << "\n";
        }
        else
        {
            processedGEDCOM << "Invalid level\n";
        }
        
        // Get tag
        string tag;
        string ID;
        tag = Utilities::getTag(tokenizedLine);
        if(Utilities::isINDIorFAM(tokenizedLine))
        {
            ID = Utilities::getLevelZeroID(tokenizedLine);
        }
        
        
        // Check if tag is valid
        if(Utilities::isValidTag(tag))
        {
            processedGEDCOM << tag << "\n";
        }
        else
        {
            processedGEDCOM << "Invalid tag\n";
            
            // Dont process anything else, skip to next line
            continue;
        }
        
        // Add line to individual
        if(levelZeroTAG == "INDI")
        {
            // Get INDI mapped to levelZeroID
            Individual i = manager->lookupIndividual(levelZeroID);
            if(level == 1 && tag == "NAME")
            {
                string name = tokenizedLine[2] + " " + tokenizedLine[3];
                i.setName(name);
				i.setLineNumber(lineNumber - 1);//Subtract 1 to get the idx of INDI
                manager->addIndividual(levelZeroID, i);
            }
			else if (level == 1 && tag == "SEX")
			{
				i.setSex(tokenizedLine[2]);
				manager->addIndividual(levelZeroID, i);
			}
			else if (level == 1 && tag == "BIRT")
			{
				levelOneTAG = "BIRT";
			}
			else if (level == 1 && tag == "DEAT")
			{
				levelOneTAG = "DEAT";
			}
			else if (level == 1 && tag == "FAMS")
			{
				i.setFAMS(tokenizedLine[2]);
				manager->addIndividual(levelZeroID, i);
			}
			else if (level == 1 && tag == "FAMC")
			{
				i.setFAMC(tokenizedLine[2]);
				manager->addIndividual(levelZeroID, i);
			}
			else if (level == 2 && tokenizedLine[1] == "DATE")
			{
				Date d(line);
				if (levelOneTAG == "BIRT")
				{
					i.setBirth(d);
					manager->addIndividual(levelZeroID, i);
				}
				else if (levelOneTAG == "DEAT")
				{ 
					i.setDeath(d);
					manager->addIndividual(levelZeroID, i);
				}
			}
        }
        
        if(levelZeroTAG == "FAM")
        {
            // Get FAM mapped to levelZeroID
            Family f = manager->lookupFamily(levelZeroID);
			if (f.getId() == "")
			{
				f.setId(levelZeroID);
			}
            if(level == 1 && tag == "HUSB")
            {
                // Add husband
				f.setHusband(tokenizedLine[2]);
				f.setLineNumber(lineNumber - 1);//Subtract 1 to get the idx of FAM
				manager->addFamily(levelZeroID, f);
            }
            else if(level == 1 && tag == "WIFE")
            {
                // Add wife
				f.setWife(tokenizedLine[2]);
				manager->addFamily(levelZeroID, f);
            }
			else if (level == 1 && tag == "MARR")
			{
				levelOneTAG = "MARR";
			}
			else if (level == 1 && tag == "DIV")
			{
				levelOneTAG = "DIV";
			}
			else if (level == 1 && tag == "CHIL")
			{
				// Add Child
				levelOneTAG = "CHIL";
				f.addChild(tokenizedLine[2]);
				manager->addFamily(levelZeroID, f);
			}
			else if (level == 2 && tokenizedLine[1] == "DATE")
			{
				Date d(line);
				if (levelOneTAG == "MARR")
				{
					f.setMarried(d);
					manager->addFamily(levelZeroID, f);
				}
				else if (levelOneTAG == "DIV")
				{
					f.setDivorced(d);
					manager->addFamily(levelZeroID, f);
				}
			}
        }
        
        if(tag == "INDI")
        {
            // Store empty INDI with unique ID
			levelZeroID = manager->addIndividual(ID, lineNumber, errorFileName);

            // Set levelZero variables to process other lines for INDI
            levelZeroTAG = tag;
			levelOneTAG = "";
        }
        
        if(tag == "FAM")
        {
            // Store empty INDI with unique ID
			levelZeroID = manager->addFamily(ID, lineNumber, errorFileName);
            
            // Set levelZero variables to process other lines for FAM
            levelZeroTAG = tag;
			levelOneTAG = "";
        }
    } // while (getline(gedcomFile, line))
    
    manager->printIndividuals(inputFileName);
    manager->printFamilies(inputFileName);
	manager->printLivingMarried(inputFileName);
	manager->printLivingSingle(inputFileName);
	manager->printDeceased(inputFileName);
	manager->printOrphans(inputFileName);
	manager->printMultipleBirths(inputFileName);
	manager->buildIndividualMarriages();
	manager->errorCheck(errorFileName);
	manager->printRecentBirths(inputFileName, 30);
	manager->printRecentDeaths(inputFileName, 30);

    processedGEDCOM.close();
}