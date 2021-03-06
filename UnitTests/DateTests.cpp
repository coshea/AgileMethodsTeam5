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


		TEST_METHOD(TestAddMonths_Positive)
		{
			Date startDate(20, 9, 2017);
			Date expectedDate(20, 2, 2018);
			int monthsAdded = 5;

			startDate.AddMonths(monthsAdded);
			
			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddMonths_Negative)
		{
			Date startDate(20, 1, 2017);
			Date expectedDate(20, 11, 2016);
			int monthsAdded = -2;

			startDate.AddMonths(monthsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddMonths_ChangeToEndOfMonth)
		{
			Date startDate(31, 1, 2017);
			Date expectedDate(30, 4, 2017);
			int monthsAdded = 3;

			startDate.AddMonths(monthsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddMonths_ChangeToEndOfMonth_LeapYear)
		{
			Date startDate(31, 1, 2016);
			Date expectedDate(29, 2, 2016);
			int monthsAdded = 1;

			startDate.AddMonths(monthsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddYears_Positive)
		{
			Date startDate(20, 9, 2017);
			Date expectedDate(20, 9, 2022);
			int yearsAdded = 5;

			startDate.AddYears(yearsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddYears_Negative)
		{
			Date startDate(20, 1, 2017);
			Date expectedDate(20, 1, 2015);
			int yearsAdded = -2;

			startDate.AddYears(yearsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddYears_LeapDay_NewDateNotLeapDay)
		{
			Date startDate(29, 2, 2016);
			Date expectedDate(1, 3, 2017);
			int yearsAdded = 1;

			startDate.AddYears(yearsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddYears_LeapDay_NewDateIsLeapDay)
		{
			Date startDate(29, 2, 2016);
			Date expectedDate(29, 2, 2020);
			int yearsAdded = 4;

			startDate.AddYears(yearsAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestEndOfMonthDay_31)
		{
			Date testDate(19, 1, 2016);
			int expectedValue = 31;

			int actualValue =testDate.getEndOfMonthDay();
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestEndOfMonthDay_30)
		{
			Date testDate(19, 4, 2016);
			int expectedValue = 30;

			int actualValue = testDate.getEndOfMonthDay();
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestEndOfMonthDay_29)
		{
			Date testDate(19, 2, 2016);
			int expectedValue = 29;

			int actualValue = testDate.getEndOfMonthDay();
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestEndOfMonthDay_28)
		{
			Date testDate(19, 2, 2017);
			int expectedValue = 28;

			int actualValue = testDate.getEndOfMonthDay();
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Positive)
		{
			Date startDate(20, 1, 2017);
			Date expectedDate(22, 1, 2017);
			int daysAdded = 2;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Positive_AddMonth)
		{
			Date startDate(29, 1, 2017);
			Date expectedDate(3, 2, 2017);
			int daysAdded = 5;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Positive_AddMonth_AddYear)
		{
			Date startDate(29, 12, 2017);
			Date expectedDate(3, 1, 2018);
			int daysAdded = 5;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Negative)
		{
			Date startDate(22, 1, 2017);
			Date expectedDate(20, 1, 2017);
			int daysAdded = -2;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Negative_AddMonth)
		{
			Date startDate(3, 2, 2017);
			Date expectedDate(29, 1, 2017);
			int daysAdded = -5;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestAddDays_Negative_AddMonth_AddYear)
		{
			Date startDate(3, 1, 2018);
			Date expectedDate(29, 12, 2017);
			int daysAdded = -5;

			startDate.AddDays(daysAdded);

			bool expectedValue = true;
			bool actualValue = startDate == expectedDate;
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIncludePartialDates_DayMonthYear_Valid)
		{
			string line = "2 DATE 13 MAR 1999";
			Date testDate(line);
			Date expectedDate(13, 3, 1999);

			bool actualValue = testDate.isDateValid();
			Assert::IsTrue(actualValue, L"message", LINE_INFO());

			bool actualDateCompareValue = testDate == expectedDate;
			Assert::IsTrue(actualDateCompareValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIncludePartialDates_MonthYear_Valid)
		{
			string line = "2 DATE MAR 1999";
			Date testDate(line);
			Date expectedDate(1, 3, 1999);

			bool actualValue = testDate.isDateValid();
			Assert::IsTrue(actualValue, L"message", LINE_INFO());

			bool actualDateCompareValue = testDate == expectedDate;
			Assert::IsTrue(actualDateCompareValue, L"message", LINE_INFO());
		}

		TEST_METHOD(TestIncludePartialDates_Year_Valid)
		{
			string line = "2 DATE 1999";
			Date testDate(line);
			Date expectedDate(1, 1, 1999);

			bool actualValue = testDate.isDateValid();
			Assert::IsTrue(actualValue, L"message", LINE_INFO());

			bool actualDateCompareValue = testDate == expectedDate;
			Assert::IsTrue(actualDateCompareValue, L"message", LINE_INFO());
		}

	};
}