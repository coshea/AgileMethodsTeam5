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

// Main function
int main(int argc, const char * argv[])
{
    
    GEDCOMManager *manager = GEDCOMManager::Instance();
    
    // Input file
    ifstream gedcomFile(argv[1]);
    
    // Output file
    string outputFileName = "processed" + string(argv[1]);
    ofstream processedGEDCOM(outputFileName);
    
    // read lines from input file
    string line;
    string levelZeroID;
    string levelZeroTAG;
    while (getline(gedcomFile, line))
    {
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
                manager->addIndividual(levelZeroID, i);
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
        }
        
        if(tag == "INDI")
        {
            // Store empty INDI with unique ID
            manager->addIndividual(ID);
            
            // Set levelZero variables to process other lines for INDI
            levelZeroID = ID;
            levelZeroTAG = tag;
        }
        
        if(tag == "FAM")
        {
            // Store empty INDI with unique ID
            manager->addFamily(ID);
            
            // Set levelZero variables to process other lines for FAM
            levelZeroID = ID;
            levelZeroTAG = tag;
        }
    } // while (getline(gedcomFile, line))
    
    manager->printIndividuals(argv[1]);
    manager->printFamilies(argv[1]);
    
    processedGEDCOM.close();
}