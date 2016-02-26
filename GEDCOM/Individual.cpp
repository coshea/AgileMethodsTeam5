//
//  Individual.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "Individual.h"

Individual::Individual()
{
    m_name = "";
    m_sex = "";
	m_birth = { 0, 0, 0 };
	m_death = { 0, 0, 0 };
    m_famChild = "";
    m_famSpouse = "";
	m_lineNumber = -1;
}

void Individual::setName(string n)
{
    m_name = n;
}

string Individual::getName()
{
    return m_name;
}

void Individual::setSex(string s)
{
    m_sex = s;
}

string Individual::getSex()
{
    return m_sex;
}

void Individual::setBirth(Date b)
{
    m_birth = b;
}

Date Individual::getBirth()
{
    return m_birth;
}

void Individual::setDeath(Date d)
{
    m_death = d;
}

Date Individual::getDeath()
{
    return m_death;
}

void Individual::setFAMC(string famc)
{
    m_famChild = famc;
}

string Individual::getFAMC()
{
    return m_famChild;
}

void Individual::setFAMS(string fams)
{
    m_famSpouse = fams;
}

string Individual::getFAMS()
{
    return m_famSpouse;
}

void Individual::setLineNumber(int lineNum)
{
	m_lineNumber = lineNum;
}

int Individual::getLineNumber()
{
	return m_lineNumber;
}