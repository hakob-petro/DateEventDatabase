#include "database.h"

#include <algorithm>
#include <stdexcept>

using namespace std;
 
DateEvent::DateEvent(const Date& date, const string& event) : date_(date), event_(event){}

ostream& operator << (ostream& stream, const DateEvent& de)
{
	stream << de.date_ << " " << de.event_;
	return stream;
}

void Database::Add(const Date& date, const string& event)
{
	if (base_[date].empty() == 0) base_[date].push_back(event);
	else {
		const auto it = find(base_[date].begin(), base_[date].end(), event);
		if (it == base_[date].end())
		{
			base_[date].push_back(event);
		}
	}
}

ostream& Database::Print(ostream& stream) const
{
	for(auto &elem : base_)
	{
		for(auto &event : elem.second)
		{
			stream << elem.first << " " << event << endl;
		}
	}
	return stream;
}

DateEvent Database::Last(const Date& date) const
{
	// it points to the first DateEvent with date more then given 
	const auto it = find_if_not(begin(base_), end(base_),
		[date](const pair<const Date, vector<string>>& pr)->bool{ return pr.first <= date; });
	if (it == end(base_)) throw invalid_argument("No events with date less then given!");
	// it->second[it->second.size() - 1] the last event of vector
	return {it->first, it->second[it->second.size() - 1]}; // return the date and the last event	
}
