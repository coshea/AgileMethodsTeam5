#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "CppUnitTest.h"
#include "../GEDCOM/Family.h"
#include "../GEDCOM/Individual.h"
#include "../GEDCOM/Errors.h"
#include "../GEDCOM/GEDCOMManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ErrorTests)
	{
	public:

		TEST_METHOD(Test_AreGendersCorrectTrue)
		{
			Family fam;
			Individual husb;
			Individual wife;
			GEDCOMManager * manager = GEDCOMManager::Instance();

			husb.setSex("M");
			wife.setSex("F");
			husb.setLineNumber(0);
			wife.setLineNumber(0);
			manager->addIndividual("HUSB", husb);
			manager->addIndividual("WIFE", wife);

			fam.setHusband("HUSB");
			fam.setWife("WIFE");

			manager->addFamily("FAM", fam);

			remove("UnitTestResults.txt");
			CorrectGender("UnitTestResults.txt", "FAM");
			ifstream resultsFile("UnitTestResults.txt");

			bool expectedValue = true;
			bool actualValue;
			if (FILE* file = fopen("UnitTestResults.txt", "r"))
			{
				actualValue = true;
				fclose(file);
			}
			else
			{
				actualValue = false;
			}
			Assert::AreEqual(false, actualValue, L"Genders are incorrect", LINE_INFO());
		}

		TEST_METHOD(Test_AreGendersCorrectFalse)
		{
			FILE * fileID;
			Family fam;
			Individual husb;
			Individual wife;
			GEDCOMManager * manager = GEDCOMManager::Instance();

			husb.setSex("F");
			wife.setSex("M");
			husb.setLineNumber(0);
			wife.setLineNumber(0);

			manager->addIndividual("HUSB", husb);
			manager->addIndividual("WIFE", wife);

			fam.setHusband("HUSB");
			fam.setWife("WIFE");

			manager->addFamily("FAM", fam);

			remove("UnitTestResults.txt");
			CorrectGender("UnitTestResults.txt", "FAM");
			ifstream resultsFile("UnitTestResults.txt");

			bool expectedValue = true;
			bool actualValue = false;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

	};
}