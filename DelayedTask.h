#pragma once
#include "task.h"
#include "SimpleTask.h"

struct delayedTask : public task
{
	void indicateCreation() override; // can use strategy pattern
	void generateTask() override;
	void indicateTaskPush(std::string simpleTaskName, std::string simpleTaskQueueName);
	delayedTask(std::string name, std::string queue, int delay);
};