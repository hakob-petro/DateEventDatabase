#pragma once
#include <sstream>

struct Date
{
	Date(int& year, int& month, int& day);
	
	 int year_;
	 int month_;
	 int day_;
};

Date ParseDate(std::istringstream& is);

std::ostream& operator << (std::ostream& stream, const Date& date);

bool operator < (const Date& date1, const Date& date2);

bool operator > (const Date& date1, const Date& date2);

bool operator == (const Date& date1, const Date& date2);

bool operator != (const Date& date1, const Date& date2);

bool operator <= (const Date& date1, const Date& date2);

bool operator >= (const Date& date1, const Date& date2);