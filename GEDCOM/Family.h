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
    
    void setMarried(Date m);
    
    Date getMarried();
    
    void setDivorced(Date d);
    
    Date getDivorced();
    
    void setHusband(string h);
    
    string getHusband();
    
    void setWife(string w);
    
    string getWife();
    
    void addChild(string child);
    
    vector<string> getChildren();

	void setLineNumber(int lineNum);

	int getLineNumber();
    
private:
	Date m_married = { 0, 0, 0 };
	Date m_divorced = { 0, 0, 0 };
    string m_husband;
    string m_wife;
    vector<string> m_children;
	int m_lineNumber;
};

#endif /* Family_h */
