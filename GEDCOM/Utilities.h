//
//  Utilities.h
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

#include <vector>

using namespace std;

namespace Utilities
{
    vector<string> validTags = {"INDI", "NAME",
        "SEX", "BIRT",
        "DEAT", "FAMC",
        "FAMS", "FAM",
        "MARR", "HUSB",
        "WIFE", "CHIL",
        "DIV", "DATE",
        "HEAD", "TRLR",
        "NOTE"};
    
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
    };
    
    bool isValidTag(string tag)
    {
        return find(validTags.begin(), validTags.end(), tag) != validTags.end();
    };
    
    bool isLevelZeroTag(string tag)
    {
        return find(validTags.begin(), validTags.end(), tag) != validTags.end();
    };
    
    int getLevel(vector<string> line)
    {
        int level;
        try
        {
            level = stoi(line[0]);
        }
        catch(exception ex)
        {
            // Invalid level
            level = -1;
        }
        return level;
    };
    
    bool isINDIorFAM(vector<string> line)
    {
        if(find(line.begin(), line.end(), "INDI") != line.end() ||
           find(line.begin(), line.end(), "FAM") != line.end())
        {
            return true;
        }
        else    // 0 <tag> <arguments that may be ignored>
        {
            return false;
        }
    }
    
    string getTag(vector<string> line)
    {
        string tag;
        // 0 <xref-id> <tag>
        if(find(line.begin(), line.end(), "INDI") != line.end() ||
           find(line.begin(), line.end(), "FAM") != line.end())
        {
            tag = line[2];
        }
        else    // 0 <tag> <arguments that may be ignored>
        {
            tag = line[1];
        }
        
        return tag;
    };
    
    string getLevelZeroID(vector<string> line)
    {
        return line[1];
    };
    
}

#endif /* Utilities_h */
