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
    name = "";
    sex = "";
	birth = { 0, 0, 0 };
	death = { 0, 0, 0 };
    famChild = "";
    famSpouse = "";
}

void Individual::setName(string n)
{
    name = n;
}

string Individual::getName()
{
    return name;
}

void Individual::setSex(string s)
{
    sex = s;
}

string Individual::getSex()
{
    return sex;
}

void Individual::setBirth(Date b)
{
    birth = b;
}

Date Individual::getBirth()
{
    return birth;
}

void Individual::setDeath(Date d)
{
    death = d;
}

Date Individual::getDeath()
{
    return death;
}

void Individual::setFAMC(string famc)
{
    famChild = famc;
}

string Individual::getFAMC()
{
    return famChild;
}

void Individual::setFAMS(string fams)
{
    famSpouse = fams;
}

string Individual::getFAMS()
{
    return famSpouse;
}