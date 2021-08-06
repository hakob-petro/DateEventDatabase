#include "date.h"

#include <vector>

using namespace std;

Date::Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day) {}

Date ParseDate(istringstream& is)
{
	vector<const int> date;
	int number = 0 ;
	while (is >> number && date.size()!=3) {
		is.ignore(1);
		date.push_back(number);
	}
	return {date[0], date[1], date[2]};
}

ostream& operator << (ostream& stream, const Date &date)
{
	stream << date.year_ << "-" << date.month_ << "_" << date.day_;
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
	return !(date1 < date2);
}

bool operator != (const Date& date1, const Date& date2)
{
	return !(date1 == date2);
}

bool operator <= (const Date& date1, const Date& date2)
{
	return date1 < date2 || date1 == date2;
}

bool operator >= (const Date& date1, const Date& date2)
{
	return date1 > date2 || date1 == date2;
}