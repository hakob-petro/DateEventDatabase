#pragma once
#include "date.h"

#include <set>
#include <map>
#include <string>
#include <vector>
#include <functional>

using Predicate = std::function<bool(const Date& date, const std::string& event)>;

struct Entry
{
	Entry(const Date& date, const std::string& event);
	
	const Date date_;
	const std::string event_;
};

std::ostream& operator << (std::ostream& stream, const Entry& de);

bool operator < (const Entry& entry1, const Entry& entry2);

bool operator == (const Entry& entry1, const Entry& entry2);

bool operator > (const Entry& entry1, const Entry& entry2);


class Database
{
public:
	void Add(const Date& date, const std::string& event);
	
	std::ostream& Print(std::ostream& stream) const;
	
	Entry Last(const Date& date) const;

	int RemoveIf(const Predicate& predicate);

	std::vector<Entry> FindIf(const Predicate& predicate) const;

private:
	std::multiset<Entry, std::less<>> base_;
	std::map<Date, std::set<std::string>> check_base_;
};
