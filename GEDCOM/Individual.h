//
//  Individual.h
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef Individual_h
#define Individual_h

class Date;

#include "Date.h"
#include <string>

using namespace std;

class Individual
{
public:
    Individual();
    
    void setName(string n);
    
    string getName();

	string getLastName();
    
    void setSex(string s);
    
    string getSex();
    
    void setBirth(Date b);
    
    Date getBirth();
    
    void setDeath(Date d);
    
    Date getDeath();
    
    void setFAMC(string famc);
    
    string getFAMC();
    
    void setFAMS(string fams);
    
    string getFAMS();
    
	void setLineNumber(int lineNum);

	int getLineNumber(void);

	bool isDead();

	int getAge();

private:
    string m_name;
    string m_sex;
    Date   m_birth;
    Date   m_death;
    string m_famChild;
    string m_famSpouse;
	int m_lineNumber;
};

#endif /* Individual_h */
