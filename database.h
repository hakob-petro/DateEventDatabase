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

ostream& operator << (ostream& stream, const DateEvent& ivent);

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
	map<Date, vector<string>> base_;
	// unordered_set<pair<Date, string>>; - sax variantnery linum a shat hesht. Lasty zut miangam ciklov frum enq
};
