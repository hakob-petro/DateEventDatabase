#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
//#include "test_db.h"

#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
	string event;
	getline(is >> std::ws, event);
	return event;
}

// void TestAll();

int main() {
	// run all configured tests
	//TestAll();
	// if it is okay run the next part
	
	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add")
		{
			const Date date = ParseDate(is); 
			const string event = ParseEvent(is);
			db.Add(date, event);
		}
		else if (command == "Print") 
		{
			db.Print(cout);
		}
		else if (command == "Del")
		{
			shared_ptr<Node> condition = ParseCondition(is);

			// lambda expression that for each date and event evaluate true it or false
			auto predicate = [condition](const Date& date, const string& event)->bool
			{
				return condition->Evaluate(date, event);
			};
			
			const int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find") 
		{
			shared_ptr<Node> condition = ParseCondition(is);

			// lambda expression that for each date and event evaluate true it or false
			auto predicate = [condition](const Date& date, const string& event)->bool
			{
				return condition->Evaluate(date, event);
			};

			const vector<Entry> entries = db.FindIf(predicate);
			for (const Entry& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last") 
		{
			try {
				cout << db.Last(ParseDate(is)) << endl;
			} catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		}
		else if (command.empty()) 
		{
			continue;
		} else {
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}

// test function ParseEvent
void TestParseEvent() {
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
	}
}

// test functions ParseEvent and ParseCondition and others...
//void TestAll() {
//	TestRunner tr;
//	tr.RunTest(TestParseEvent, "TestParseEvent");
//	tr.RunTest(TestParseCondition, "TestParseCondition");
//	tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
//	tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
//	tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
//	tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
//	tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
//	tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
//	tr.RunTest(TestsMyCustom, "Мои тесты");
//	tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
//}