#pragma once
#include <map>
#include <string>
#include <vector>

#include "date.h"

using namespace std;

struct DateEvent
{
	DateEvent(const Date& date, const string& event);
	
	const Date date_;
	const string event_;
};

ostream& operator << (ostream& stream, const DateEvent& de);

class Database
{
public:
	void Add(const Date& date, const string& event);
	
	ostream& Print(ostream& stream) const;

	template<typename T>
	int RemoveIf(T predicate);

	template<typename T>
	vector<DateEvent> FindIf(T predicate);
	
	DateEvent Last(const Date& date) const;

private:
	map<const Date, vector<const string>> base_;
};
