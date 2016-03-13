//
//  Errors.h
//  GEDCOM
//
//  Created by M. Scully on 2/21/16.
//

#ifndef Errors_h
#define Errors_h

void BirthBeforeDeath(string fileName, string first, Individual &i);
void BirthBeforeMarriage(string fileName, string first, Individual &i, Family &f);
void MarriageBeforeDivorce(string fileName, string first, Individual &i, Family &f);
void MarriageBeforeDeath(string fileName, string first, Individual &i, Family &f);
void DivorceBeforeDeath(string fileName, string first, Individual &i, Family &f);
void IsDateValid(string fileName, string first, Individual &i);
void CorrectGender(string fileName, string familyID);
string CorrectRepeatedID(string id, int currentLineNum, int firstLineNum, string fileName);
void ChildsBirthBeforeMarriage(string fileName, Family &f);
void ChildsBirthBeforeMarriage(string fileName, Individual &i);
#endif /* Errors_h */
