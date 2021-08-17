#include "../include/node.h"

using namespace std;

// Definig class constructors
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& oper, const shared_ptr<Node>& left, const shared_ptr<Node>& right)
					: oper_(oper), left_(left), right_(right) {}

// Defining EmptyNode class methods
bool EmptyNode::Evaluate(const Date& date, const string& event)
{
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch(cmp_)
	{
	case Comparison::Equal:
		return date == date_;
	case Comparison::NotEqual:
		return date != date_;
	case Comparison::Less:
		return date < date_;
	case Comparison::LessOrEqual:
		return date <= date_;
	case Comparison::Greater:
		return date > date_;
	case Comparison::GreaterOrEqual:
		return date >= date_;
	}
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (cmp_)
	{
	case Comparison::Equal:
		return event == event_;
	case Comparison::NotEqual:
		return event != event_;
	case Comparison::Less:
		return event < event_;
	case Comparison::LessOrEqual:
		return event <= event_;
	case Comparison::Greater:
		return event > event_;
	case Comparison::GreaterOrEqual:
		return event >= event_;
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)
{
	switch (oper_) {
	case LogicalOperation::Or:
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	case LogicalOperation::And:
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}
	return true;
}