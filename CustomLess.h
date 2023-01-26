#pragma once
#include "SimpleTask.h"
#include <memory>

struct customLess
{
	bool operator() (const std::shared_ptr <simpleTask>& left, const std::shared_ptr <simpleTask>& right)
	{
		return (left.get())->SimpleTaskPriority > (right.get())->SimpleTaskPriority;
	}
};