//
//  Individual.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "Individual.h"
#include <time.h>

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

string Individual::getLastName()
{
	size_t pos = m_name.find(" ") + 1;
	if (pos == string::npos)
		return "";

	return m_name.substr(pos, string::npos);
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

bool Individual::isDead()
{
	if (m_death.getDay() == 0 && m_death.getMonth() == 0 && m_death.getYear() == 0)
		return false;
	else
		return true;
}

int Individual::getAge()
{
	int years = 0;

	if (isDead())
	{
		years = m_death.getYear() - m_birth.getYear();
		if (m_birth.getMonth() == m_death.getMonth())
		{
			if (m_birth.getDay() > m_death.getDay())
				years--;
		}
		else if (m_birth.getMonth() > m_death.getMonth())
			years--;
	}
	else 
	{
		time_t currentTime = time(0);	
		struct tm compareDate;
		localtime_s(&compareDate, &currentTime);

		years = (compareDate.tm_year + 1900) - m_birth.getYear();
		if (m_birth.getMonth() == (compareDate.tm_mon + 1))
		{
			if (m_birth.getDay() > (compareDate.tm_mday))
				years--;
		}
		else if (m_birth.getMonth() > (compareDate.tm_mon + 1))
			years--;
	}
		
	
	return years;
}

void Individual::addSibling(string sib) 
{
	m_siblings.push_back(sib);
}

vector<string> Individual::getSiblings(void)
{
	return m_siblings;
}