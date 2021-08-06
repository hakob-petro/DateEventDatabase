#include <algorithm>
#include <stdexcept>

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
	vector<string> &events = base_[date];
	if (events.empty() == 0) events.push_back(event);
	else {
		vector<string>::iterator it = find(base_[date].begin(), base_[date].end(), event);
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
	const auto base_begin_iter = begin(base_), base_end_iter = end(base_);
	while (base_begin_iter != base_end_iter && base_begin_iter->first < date)
	{
		next(base_begin_iter);
	}
	if (base_begin_iter == begin(base_)) throw invalid_argument("There is no date smaller than given.");
	return  {base_begin_iter->first, base_begin_iter->second[base_begin_iter->second.size() - 1]}; // cout the date and last events
	
}


template<typename T>
int Database::RemoveIf(T predicate)
{
	auto map_iter = begin(base_);
	while(map_iter!=end(base_))
	{
		auto vector_iter = begin(map_iter->second);
		for(vector_iter; vector_iter != end(map_iter->second); next(vector_iter))
		stable_partition(begin(base_), end(base_), predicate());
	}
}

template<typename T>
vector<DateEvent> Database::FindIf(T predicate)
{
	
}


