#include <algorithm>
#include <stdexcept>
//#include <functional>

#include "database.h"

using namespace std;

DateEvent::DateEvent(const Date& date, const string& event) : date_(date), event_(event){};

ostream& operator << (ostream& stream, const DateEvent& de)
{
	stream << de.date_ << " " << de.event_;
	return stream;
}

void Database::Add(const Date& date, const string& event)
{
	vector<const string> &events = base_[date];
	if (events.empty() == 0) events.push_back(event);
	else {
		vector<const string>::iterator it = find(base_[date].begin(), base_[date].end(), event);
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
	const auto it = find_if_not(begin(base_), end(base_),
		[date](pair<const Date, vector<const string>>& pr) { return pr.first <= date; });
	if (it == end(base_)) throw invalid_argument("No events with date less then given!");
	return  {it->first, it->second[it->second.size() - 1]}; // cout the date and last events
	
}


template<typename T>
int Database::RemoveIf(T predicate)
{
	int count = 0;
	auto map_iter = begin(base_);
	while(map_iter != end(base_))
	{
		const Date &date = map_iter->first;

		auto lambda = [date, predicate](const string& event) { return !predicate(date, event); };
		
		auto &vector_events = map_iter->second;
		auto iter = stable_partition(begin(vector_events), end(vector_events), lambda);

		int i = end(vector_events) - iter;
		while(i > 0)
		{
			vector_events.pop_back();
			++count;
			--i;
		}
		++map_iter;
	}
	return count;
}

template<typename T>
vector<DateEvent> Database::FindIf(T predicate)
{
	vector<DateEvent> result;
	auto map_iter = begin(base_);
	while (map_iter != end(base_))
	{
		const Date &date = map_iter->first;
		
		auto lambda = [date, predicate](const string& event) { return predicate(date, event); };

		auto &vector_events = map_iter->second;

		int count = 0;
		while (count != end(vector_events) - begin(vector_events)) {
			auto iter = find_if(begin(vector_events) + count, end(vector_events), lambda);
			count = iter - begin(vector_events);
			++count;
			result.push_back(*iter);
		}
		
		++map_iter;
	}
	return result;
}


