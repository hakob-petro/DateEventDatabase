#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
	string event;
	getline(is, event);
	return event;
}

void TestAll();

int main() {
	// run all configured tests
	TestAll();
	// if it is okay run the next part
	
	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add")
		{
			const auto date = ParseDate(is); // get Date date from stream 
			const auto event = ParseEvent(is); // get string event from stream
			db.Add(date, event);
		}
		else if (command == "Print") 
		{
			db.Print(cout);
		}
		else if (command == "Del")
		{
			auto condition = ParseCondition(is); // get sahred_ptr<Node> condition from strteam

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
			auto condition = ParseCondition(is);

			// lambda expression that for each date and event evaluate true it or false
			auto predicate = [condition](const Date& date, const string& event)->bool
			{
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
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

// test functions ParseEvent and ParseCondition
void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
}
