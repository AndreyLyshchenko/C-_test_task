#pragma once
#include "SimpleTask.h"
#include <memory>

struct customLess
{
	bool operator() (const std::unique_ptr <simpleTask>& left, const std::unique_ptr <simpleTask>& right)
	{
		return (left.get())->Priority > (right.get())->Priority;
	}
};