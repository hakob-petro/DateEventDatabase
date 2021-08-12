#pragma once
#include "date.h"

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

struct Entry
{
	Entry(const Date& date, const std::string& event);
	
	const Date date_;
	const std::string event_;
};

std::ostream& operator << (std::ostream& stream, const Entry& de);

class Database
{
public:
	void Add(const Date& date, const std::string& event);
	
	std::ostream& Print(std::ostream& stream) const;
	
	Entry Last(const Date& date) const;

	// declaration of the template function RemoveIf wich will get a lambda expression prediacte (function<bool(Date, string)> from
	// library <functional>) and remove all Entrys for what predicate returns true
	// returns the count of deleted events
	template<typename T>
	int RemoveIf(T predicate)
	{
		int count = 0;
		auto map_iter = begin(base_);
		while (map_iter != end(base_))
		{
			const Date& date = map_iter->first;

			// definition of the new lambda expresion lambda (function<bool(Date, string)> from library <functional>)
			// which does that the same as the predicate, but for certain Date
			auto lambda = [date, predicate](const std::string& event)->bool { return !predicate(date, event); };

			// partition will save the order of events wich won't be deleted
			std::vector<std::string>& vector_events = map_iter->second;
			auto iter = stable_partition(begin(vector_events), end(vector_events), lambda);

			// all events that must be removed are stored in the end of vector,
			// so we count the number of that events and efficiently delete them  from the end of vector(algorithmic complexity - O(n),
			// by comparison std::vector.erase with algorithmic complexity - O(n^2))
			int i = end(vector_events) - iter;
			while (i > 0)
			{
				vector_events.pop_back();
				++count;
				--i;
			}

			// check if there are no events, delete the date
			if (vector_events.empty())
				map_iter = base_.erase(map_iter);
			else
				++map_iter;
		}
		return count;
	}

	// declaration of the template function FindIf wich will get a lambda expression prediacte (function<bool(Date, string)> from
	// library <functional>) and put into vector all Entrys for what predicate returns true
	// returns a vector that events
	template<typename T>
	std::vector<Entry> FindIf(T predicate)
	{
		std::vector<Entry> result;
		auto map_iter = begin(base_);
		while (map_iter != end(base_))
		{
			const Date& date = map_iter->first;

			// definition of the new lambda expresion lambda (function<bool(Date, string)> from library <functional>)
			// which does that the same as the predicate, but for certain Date
			auto lambda = [date, predicate](const std::string& event)->bool{ return predicate(date, event); };

			std::vector<std::string>& vector_events = map_iter->second;

			auto iter = begin(vector_events);
			while (iter != end(vector_events)) {
				iter = find_if(iter, end(vector_events), lambda);
				if (iter != end(vector_events)) {
					result.push_back({ date, *iter });
					++iter;
				}
			}

			++map_iter;
		}
		return result;
	}

private:
	std::map<Date, std::vector<std::string>> base_;
};
