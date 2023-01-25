#pragma once
#include "task.h"
#include <string>
#include <iostream>
#include <chrono>
#include <mutex>
#include <queue>

extern std::mutex consoleLocker;

struct task
{
	std::string Name;
	std::string QueueName;
	int Delay;

	void getCurrentTime();

	void sleep();

	void getTaskName();
	void getQueueName();
	void getSleepTime();

	virtual void generateTask() = 0;
	virtual void indicateCreation() = 0;

	task(std::string name, std::string queue, int delay);
};
