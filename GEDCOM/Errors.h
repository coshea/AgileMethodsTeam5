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
void MarriageBefore14(string fileName, string first, Individual &i, Family &f);
void IsDateValid(string fileName, string first, Individual &i);
void NoBigamy(string fileName, string id, vector<pair<Date, Date>> m);
void CorrectGender(string fileName, string familyID);
string CorrectRepeatedID(string id, int currentLineNum, int firstLineNum, string fileName);
void ChildsBirthBeforeMarriageAndDivorce(string fileName, Family &f);
void ChildsBirthBeforeParentsDeath(string fileName, Family & f);
void ParentsNotTooOld(string fileName, Family & f);
void SiblingSpacing(string fileName, Family & f);
void MoreThan5Births(string fileName, Family & f);
void AuntsUnclesNiecesNephews(string fileName, Family & f);
void MoreThan15Siblings(string fileName, Family & f);
void MaleLastNames(string fileName, Family & f);

#endif /* Errors_h */
