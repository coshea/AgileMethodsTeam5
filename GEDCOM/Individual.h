//
//  Individual.h
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef Individual_h
#define Individual_h

#include "Date.h"
#include <string>

using namespace std;

class Individual
{
public:
    Individual();
    
    void setName(string n);
    
    string getName();
    
    void setSex(string s);
    
    string getSex();
    
    void setBirth(Date *b);
    
    Date * getBirth();
    
    void setDeath(Date *d);
    
    Date * getDeath();
    
    void setFAMC(string famc);
    
    string getFAMC();
    
    void setFAMS(string fams);
    
    string getFAMS();
    
private:
    string name;
    string sex;
    Date *birth;
    Date *death;
    string famChild;
    string famSpouse;
};

#endif /* Individual_h */
