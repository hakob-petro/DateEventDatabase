#pragma once
#include <sstream>

struct Date
{
	Date(const int& year, const int& month, const int& day);
	
	const int year_;
	const int month_;
	const int day_;
};

Date ParseDate(std::istringstream& is);

std::ostream& operator << (std::ostream& stream, const Date& date);

bool operator < (const Date& date1, const Date& date2);

bool operator > (const Date& date1, const Date& date2);

bool operator == (const Date& date1, const Date& date2);

bool operator != (const Date& date1, const Date& date2);

bool operator <= (const Date& date1, const Date& date2);

bool operator >= (const Date& date1, const Date& date2);