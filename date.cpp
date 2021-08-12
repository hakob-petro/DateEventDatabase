#include "date.h"

using namespace std;

Date::Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day) {}

Date ParseDate(istringstream& is)
{
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	return {year, month, day};
}

ostream& operator << (ostream& stream, const Date &date)
{
	stream << date.year_ << "-";
	if(date.month_ > 10) stream << date.month_ << "-";
	else stream << "0" << date.month_ << "-";
	if(date.day_ > 10) stream << date.day_;
	else stream << "0" << date.day_;
	return stream;
}

bool operator < (const Date& date1, const Date& date2)
{
	if (date1.year_ == date2.year_)
	{
		if (date1.month_ == date2.month_) return date1.day_ < date2.day_;
		return date1.month_ < date2.month_;
	}
	return date1.year_ < date2.year_;
}

bool operator == (const Date& date1, const Date& date2)
{
	return date1.year_ == date2.year_ &&
		date1.month_ == date2.month_ &&
		date1.day_ == date2.day_;
}

bool operator > (const Date& date1, const Date& date2)
{
	return (date2 < date1);
}

bool operator != (const Date& date1, const Date& date2)
{
	return !(date1 == date2);
}

bool operator <= (const Date& date1, const Date& date2)
{
	return !(date1 > date2);
}

bool operator >= (const Date& date1, const Date& date2)
{
	return !(date1 < date2);
}