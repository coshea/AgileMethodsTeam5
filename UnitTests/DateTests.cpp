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

		TEST_METHOD(TestEqualTo_True)
		{
			Date date1(20, 1, 2017);
			Date date2(20, 1, 2017);
			
			bool expectedValue = true;
			bool actualValue = date1 == date2;
			
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestEqualTo_False)
		{
			Date date1(20, 1, 2017);
			Date date2(21, 2, 2016);

			bool expectedValue = false;
			bool actualValue = date1 == date2;

			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestLessThan_True)
		{
			Date date1(20, 1, 2016);
			Date date2(20, 1, 2017);

			bool expectedValue = true;
			bool actualValue = date1 < date2;

			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestGreaterThan_True)
		{
			Date date1(20, 1, 2017);
			Date date2(21, 2, 2016);

			bool expectedValue = true;
			bool actualValue = date1 > date2;

			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}



	};
}