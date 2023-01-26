#pragma once
#include "task.h"
#include "DelayedTask.h"

struct simpleTask : public task
{
	simpleTask(std::string name, std::string queue, int delayedTaskDelay, int simpleTaskDelay,int simpleTaskPriority);
	void indicateCreation() override;
	void generateTask() override;
	void getSleepTime() override;
	void sleep() override;
	void indicateCompletion();
};