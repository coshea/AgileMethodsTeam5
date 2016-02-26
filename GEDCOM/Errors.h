//
//  Errors.h
//  GEDCOM
//
//  Created by M. Scully on 2/21/16.
//

#ifndef Errors_h
#define Errors_h

//
void BirthBeforeDeath(string fileName, string first, Individual &i);
void BirthBeforeMarriage(string fileName, string first, Individual &i, Family &f);

#endif /* Errors_h */
