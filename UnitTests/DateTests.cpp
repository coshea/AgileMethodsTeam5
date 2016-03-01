#include "stdafx.h"
#include "CppUnitTest.h"
#include "../GEDCOM/Date.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(DateTests)
	{
	public:
		
		TEST_METHOD(TestIsValidDate_LeapYearTrue)
		{
			Date date(29, 2, 2016);

			bool actualValue = date.isDateValid();
			bool expectedValue = true;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIsValidDate_LeapYearFalse)
		{
			Date date(29, 2, 2015);

			bool actualValue = date.isDateValid();
			bool expectedValue = false;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIsInPast_True)
		{
			Date date(20, 2, 2016);

			bool actualValue = date.isInPast();
			bool expectedValue = true;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIsInPast_False)
		{
			Date date(20, 1, 2017);

			bool actualValue = date.isInPast();
			bool expectedValue = false;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

	};
}