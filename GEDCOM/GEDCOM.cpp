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
        if(level == 0)  // Handle level 0 cases
        {
            // 0 <xref-id> <tag>
            if(find(tokenizedLine.begin(), tokenizedLine.end(), "INDI") != tokenizedLine.end() ||
               find(tokenizedLine.begin(), tokenizedLine.end(), "FAM") != tokenizedLine.end())
            {
                tag = tokenizedLine[2];
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
        }
    }
    
    processedGEDCOM.close();
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