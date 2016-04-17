//
//  Family.cpp
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/19/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#include "Family.h"

Family::Family()
{
	m_married = { 0, 0, 0 };
	m_divorced = { 0, 0, 0 };
	m_husband = "";
	m_wife = "";
	//m_children;
	m_lineNumber = -1;
}

void Family::setMarried(Date m)
{
	m_married = m;
}

Date Family::getMarried()
{
    return m_married;
}

void Family::setDivorced(Date d)
{
	m_divorced = d;
}

Date Family::getDivorced()
{
    return m_divorced;
}

void Family::setHusband(string h)
{
	m_husband = h;
}

string Family::getHusband()
{
    return m_husband;
}

void Family::setWife(string w)
{
	m_wife = w;
}

string Family::getWife()
{
    return m_wife;
}

void Family::addChild(string child)
{
	m_children.push_back(child);
}

vector<string> Family::getChildren()
{
    return m_children;
}

void Family::setLineNumber(int lineNum)
{
	m_lineNumber = lineNum;
}

int Family::getLineNumber()
{
	return m_lineNumber;
}

void Family::addAunt(string aunt)
{
	m_aunts.push_back(aunt);
}

void Family::addUncle(string uncle)
{
	m_uncles.push_back(uncle);
}

vector<string> Family::getAunts()
{
	return m_aunts;
}

vector<string> Family::getUncles()
{
	return m_uncles;
}


void Family::setId(string Id)
{
	m_Id = Id;
}

string Family::getId()
{
	return m_Id;
}