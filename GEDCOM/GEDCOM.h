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

using namespace std;

vector<string> validTags = {"INDI", "NAME",
                            "SEX", "BIRT",
                            "DEAT", "FAMC",
                            "FAMS", "FAM",
                            "MARR", "HUSB",
                            "WIFE", "CHIL",
                            "DIV", "DATE",
                            "HEAD", "TRLR",
                            "NOTE"};

void tokenize(string input, vector<string>& output);