#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <mutex>
#include <queue>
#include <thread>
#include <string>

extern std::mutex consoleLocker;

struct task
{
	std::string Name;
	std::string QueueName;

	int DelayedTaskDelay;
	int SimpleTaskPriority;
	int SimpleTaskDelay;

	void getCurrentTime();

	void getTaskName();
	void getQueueName();

	virtual void getSleepTime() =0;
	virtual void sleep() = 0;
	virtual void generateTask() = 0;
	virtual void indicateCreation() = 0;

	task(std::string name, std::string queue, int delayedTaskDelay , int simpleTaskPriority, int simpleTaskDelay);
};
