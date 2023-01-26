#pragma once
#include "SimpleTask.h"
#include <thread>

struct delayedTask : public task
{
	void indicateCreation() override; 
	void generateTask() override;
	void getSleepTime() override;
	void sleep() override;
	void indicateTaskPush(std::string simpleTaskName, std::string simpleTaskQueueName);

	delayedTask(std::string name, std::string queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);
};