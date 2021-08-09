#pragma once
#include <iostream>
#include <string>
#include <map>
#include <set>

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s);

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m);

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint);

inline void Assert(bool b, const std::string& hint);

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name);

	~TestRunner();

private:
	static int fail_count;
};
