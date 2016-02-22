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
    
}

void Family::setMarried(Date m)
{
    married = m;
}

Date Family::getMarried()
{
    return married;
}

void Family::setDivorced(Date d)
{
    divorced = d;
}

Date Family::getDivorced()
{
    return divorced;
}

void Family::setHusband(string h)
{
    husband = h;
}

string Family::getHusband()
{
    return husband;
}

void Family::setWife(string w)
{
    wife = w;
}

string Family::getWife()
{
    return wife;
}

void Family::addChild(string child)
{
    children.push_back(child);
}

vector<string> Family::getChildren()
{
    return children;
}