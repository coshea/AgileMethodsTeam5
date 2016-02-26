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
#include "GEDCOM.h"
#include "Utilities.h"
#include "Individual.h"
#include "Family.h"
#include "GEDCOMManager.h"
#include "UnitTest.h"
//define consoleApp 1

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
				i.setLineNumber(lineNumber-1);//subtract 1 to get idx of level 0 tag
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
				Date d;
				d.setDay(stoi(tokenizedLine[2]));
				d.setMonth(d.stringToMonth(tokenizedLine[3]));
				d.setYear(stoi(tokenizedLine[4]));
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
            if(level == 1 && tag == "HUSB")
            {
                // Add husband
                manager->addHusbandToFamily(tokenizedLine[2], levelZeroID);
            }
            else if(level == 1 && tag == "WIFE")
            {
                // Add wife
                manager->addWifeToFamily(tokenizedLine[2], levelZeroID);
            }
			else if (level == 1 && tag == "MARR")
			{
				levelOneTAG = "MARR";
			}
			else if (level == 2 && tokenizedLine[1] == "DATE")
			{
				Date d;
				d.setDay(stoi(tokenizedLine[2]));
				d.setMonth(d.stringToMonth(tokenizedLine[3]));
				d.setYear(stoi(tokenizedLine[4]));
				if (levelOneTAG == "MARR")
				{
					f.setMarried(d);
					manager->addFamily(levelZeroID, f);
				}
			}
        }
        
        if(tag == "INDI")
        {
            // Store empty INDI with unique ID
            manager->addIndividual(ID);
            
            // Set levelZero variables to process other lines for INDI
            levelZeroID = ID;
            levelZeroTAG = tag;
			levelOneTAG = "";
        }
        
        if(tag == "FAM")
        {
            // Store empty INDI with unique ID
            manager->addFamily(ID);
            
            // Set levelZero variables to process other lines for FAM
            levelZeroID = ID;
            levelZeroTAG = tag;
			levelOneTAG = "";
        }
    } // while (getline(gedcomFile, line))
    
    manager->printIndividuals(inputFileName);
    manager->printFamilies(inputFileName);
	manager->errorCheck(inputFileName);
    
    processedGEDCOM.close();
}