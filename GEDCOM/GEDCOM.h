//
//  GEDCOM.h
//  GEDCOM
//
//  Created by Abel Rendon Jr on 2/6/16.
//  Copyright © 2016 Abel Rendon Jr. All rights reserved.
//

#ifndef GEDCOM_h
#define GEDCOM_h
#endif /* GEDCOM_h */

#include <vector>
#include <map>

using namespace std;

struct DATE
{
    int day;
    int month;
    int year;
};

struct INDI
{
    string name;
    string sex;
    DATE birth;
    DATE death;
    string famChild;
    string famSpouse;
};

struct FAM
{
    DATE married;
    DATE divorced;
    string husband;
    string wife;
    vector<string> children;
};

vector<string> validTags = {"INDI", "NAME",
                            "SEX", "BIRT",
                            "DEAT", "FAMC",
                            "FAMS", "FAM",
                            "MARR", "HUSB",
                            "WIFE", "CHIL",
                            "DIV", "DATE",
                            "HEAD", "TRLR",
                            "NOTE"};

map<string, INDI> individuals;
map<string, FAM> families;

INDI lookupIndividual(string ID);

FAM lookupFamily(string ID);

void printIndividuals(string fileName);
void printFamilies(string fileName);

void tokenize(string input, vector<string>& output);