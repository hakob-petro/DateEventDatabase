#pragma once
#include "date.h"

#include <string>

using namespace std;

enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation
{
	Or,
	And
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const string& event);
};

class EmptyNode : public Node
{
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& cmp, const Date &date);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const string &event);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& oper, const shared_ptr<Node>& left, const shared_ptr<Node>& right);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const LogicalOperation oper_;
	const shared_ptr<Node> left_, right_;
};
