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

// Main function
int main(int argc, const char * argv[])
{
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
        tokenize(line, tokenizedLine);
        
        // Get level from first token
        int level;
        try
        {
            level = stoi(tokenizedLine[0]);
        }
        catch(exception ex)
        {
            // Invalid level
            level = -1;
        }
        
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
        if(level == 0)  // Handle level 0 cases
        {
            // 0 <xref-id> <tag>
            if(find(tokenizedLine.begin(), tokenizedLine.end(), "INDI") != tokenizedLine.end() ||
               find(tokenizedLine.begin(), tokenizedLine.end(), "FAM") != tokenizedLine.end())
            {
                tag = tokenizedLine[2];
                ID = tokenizedLine[1];
            }
            else    // 0 <tag> <arguments that may be ignored>
            {
                tag =tokenizedLine[1];
            }
        }
        else // 0 <tag> <arguments that may be ignored>
        {
            tag =tokenizedLine[1];
        }
        
        // Check if tag is valid
        if(find(validTags.begin(), validTags.end(), tag) != validTags.end())
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
            INDI i = lookupIndividual(levelZeroID);
            if(level == 1 && tag == "NAME")
            {
                i.name = tokenizedLine[2] + " " + tokenizedLine[3];
                individuals[levelZeroID]=i;
            }
        }
        
        if(levelZeroTAG == "FAM")
        {
            // Get FAM mapped to levelZeroID
            FAM f = lookupFamily(levelZeroID);
            if(level == 1 && tag == "HUSB")
            {
                // Add husband
                f.husband = tokenizedLine[2];
                families[levelZeroID] = f;
            }
            else if(level == 1 && tag == "WIFE")
            {
                // Add wife
                f.wife = tokenizedLine[2];
                families[levelZeroID] = f;
            }
        }
        
        if(tag == "INDI")
        {
            // Store empty INDI with unique ID
            individuals[ID] = INDI();
            
            // Set levelZero variables to process other lines for INDI
            levelZeroID = ID;
            levelZeroTAG = tag;
        }
        
        if(tag == "FAM")
        {
            // Store empty INDI with unique ID
            families[ID] = FAM();
            
            // Set levelZero variables to process other lines for FAM
            levelZeroID = ID;
            levelZeroTAG = tag;
        }
    } // while (getline(gedcomFile, line))
    
    printIndividuals(argv[1]);
    printFamilies(argv[1]);
    
    processedGEDCOM.close();
}

// Function to lookup individual based on unique ID
// Returns INDI struct
INDI lookupIndividual(string ID)
{
    return individuals.find(ID)->second;
}

// Function to lookup family based on unique ID
// Returns FAM struct
FAM lookupFamily(string ID)
{
    return families.find(ID)->second;
}

// Loops over map of individuals and prints to file
// Maps store keys in alphabetical order
void printIndividuals(string fileName)
{
    string outputFileName = "individuals" + string(fileName);
    ofstream individualStream(outputFileName);
    for(map<string, INDI>::iterator i = individuals.begin(); i != individuals.end(); ++i)
    {
        individualStream << i->first << " " << i->second.name << "\n";
    }
    individualStream.close();
}

// Loops over map of families and prints to file
// Maps store keys in alphabetical order
void printFamilies(string fileName)
{
    string outputFileName = "families" + string(fileName);
    ofstream familyStream(outputFileName);
    for(map<string, FAM>::iterator f = families.begin(); f != families.end(); ++f)
    {
        familyStream << f->first << "\n\t"
        << "Husband: " << lookupIndividual(f->second.husband).name << "\n\t"
        << "Wife: " << lookupIndividual(f->second.wife).name << "\n";
    }
    familyStream.close();
}

// Function to split string into a vector based on whitespace
void tokenize(string input, vector<string>& output)
{
    string token;
    for(int i = 0; i <= input.size(); i++)
    {
        if(isspace(input[i]) || i == input.size())
        {
            output.push_back(token);
            token = "";
        }
        else
        {
            token+= input[i];
        }
    }
    
}