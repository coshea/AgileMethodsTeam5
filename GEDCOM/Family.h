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
    
	void addAunt(string aunt);

	void addUncle(string uncle);

	void addCousin(string cousin);

	vector<string> getAunts();

	vector<string> getUncles();

    vector<string> getChildren();

	vector<string> getCousins();

	void setLineNumber(int lineNum);

	int getLineNumber();

	void setId(string Id);

	string getId();
    
private:
	Date m_married = { 0, 0, 0 };
	Date m_divorced = { 0, 0, 0 };
    string m_husband;
    string m_wife;
    vector<string> m_children;
	vector<string> m_aunts;
	vector<string> m_uncles;
	vector<string> m_cousins;
	int m_lineNumber;
	string m_Id;
};

#endif /* Family_h */1
