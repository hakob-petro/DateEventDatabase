#pragma once
#include "date.h"

#include <string>

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
	virtual bool Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode : public Node
{
	bool Evaluate(const Date& date, const std::string& event) override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& cmp, const Date &date);
	bool Evaluate(const Date& date, const std::string& event) override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const std::string &event);
	bool Evaluate(const Date& date, const std::string& event) override;

private:
	const Comparison cmp_;
	const std::string event_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& oper, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right);
	bool Evaluate(const Date& date, const std::string& event) override;

private:
	const LogicalOperation oper_;
	const std::shared_ptr<Node> left_, right_;
};
