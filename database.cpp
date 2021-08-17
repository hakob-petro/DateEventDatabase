#include "database.h"

#include <stdexcept>
#include <iostream>
using namespace std;
 
Entry::Entry(const Date& date, const string& event) : date_(date), event_(event){}

ostream& operator << (ostream& stream, const Entry& de)
{
	stream << de.date_ << " " << de.event_;
	return stream;
}

bool operator < (const Entry& entry1, const Entry& entry2)
{
	return entry1.date_ < entry2.date_;
}

bool operator > (const Entry& entry1, const Entry& entry2)
{
	return entry1.date_ > entry2.date_;
}

bool operator == (const Entry& entry1, const Entry& entry2)
{
	return entry1.date_ == entry2.date_ &&
		entry1.event_ == entry2.event_;
}

void Database::Add(const Date& date, const string& event)
{
	if(check_base_[date].count(event) == 0)
	{
		base_.insert({date, event});
		check_base_[date].insert(event);
	}
}

ostream& Database::Print(ostream& stream) const
{
	for (const Entry& entry : base_)
	{
		stream << entry.date_ << " " << entry.event_ << endl;
	}

	return stream;
}

Entry Database::Last(const Date& date) const
{
	const Entry empty_entry = {date, ""};
	// it points to the first Entry with date more then given 
	auto it = base_.upper_bound(empty_entry);

	if (it == begin(base_)) throw invalid_argument("No events with date less then given!");
	// --it points to the last Entry with date not less then given
	--it;
	return *it; // return the date and the last event
}

int Database::RemoveIf(const Predicate& predicate)
{
	int count = 0;
	
	for(auto it = base_.begin(); it != base_.end();)
	{
		if (predicate(it->date_, it->event_))
		{
			check_base_[it->date_].erase(it->event_);
			it = base_.erase(it);
			++count;
		}
		else
		{
			++it;
		}
	}
	return count;
}

std::vector<Entry> Database::FindIf(const Predicate& predicate) const
{
	vector<Entry> found;
	
	for(const Entry &entry : base_)
	{
		if (predicate(entry.date_, entry.event_))
		{
			found.push_back(entry);
		}
	}
	return found;
}
