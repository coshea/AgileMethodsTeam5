//
//  Family.hpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef Family_h
#define Family_h

#include "Date.h"
#include <string>
#include <vector>

using namespace std;

class Family
{
public:
    Family();
    
    void setMarried(Date * m);
    
    Date * getMarried();
    
    void setDivorced(Date * d);
    
    Date * getDivorced();
    
    void setHusband(string h);
    
    string getHusband();
    
    void setWife(string w);
    
    string getWife();
    
    void addChild(string child);
    
    vector<string> getChildren();
    
private:
    Date *married;
    Date *divorced;
    string husband;
    string wife;
    vector<string> children;
};

#endif /* Family_h */
