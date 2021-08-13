#include "database.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;
 
Entry::Entry(const Date& date, const string& event) : date_(date), event_(event){}

ostream& operator << (ostream& stream, const Entry& de)
{
	stream << de.date_ << " " << de.event_;
	return stream;
}

void Database::Add(const Date& date, const string& event)
{
	const auto it = find(base_[date].begin(), base_[date].end(), event);
	if (it == base_[date].end())
	{
		base_[date].push_back(event);
	}
}

ostream& Database::Print(ostream& stream) const
{
	for(const pair<const Date, vector<string>> &elem : base_)
	{
		for(const string &event : elem.second)
		{
			stream << elem.first << " " << event << endl;
		}
	}
	return stream;
}

Entry Database::Last(const Date& date) const
{
	// it points to the first Entry with date more then given 
	auto it = base_.upper_bound(date);
	
	if (it == begin(base_)) throw invalid_argument("No events with date less then given!");
	// --it points to the last Entry with date not less then given
	--it;
	return {it->first, it->second.back()}; // return the date and the last event	
}
