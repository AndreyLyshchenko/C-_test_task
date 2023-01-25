#pragma once
#include "task.h"
#include "DelayedTask.h"




struct simpleTask : public task
{
	int Priority;
	simpleTask(std::string name, std::string queue, int delay, int priority);
	void indicateCreation() override;
	void generateTask() override;
	void indicateCompletion();
	simpleTask& operator = (const simpleTask& task);
};