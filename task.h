#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <mutex>
#include <queue>
#include <thread>


struct queueContainer;
struct baseQueue;
struct simpleQueue;
struct delayQueue;

extern std::mutex consoleLocker;

struct task;
struct delayedTask;
struct simpleTask;


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
	virtual void generateTask(queueContainer& containerLink) = 0;
	virtual void indicateCreation() = 0;

	task(const std::string& name, const std::string& queue, int delayedTaskDelay , int simpleTaskPriority, int simpleTaskDelay);
};

struct delayedTask : public task
{
	void indicateCreation() override;
	void generateTask(queueContainer& containerLink) override;
	void getSleepTime() override;
	void sleep() override;
	void indicateTaskPush(const std::string& simpleTaskName, const std::string& simpleTaskQueueName);

	delayedTask(const std::string& name, const std::string& queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);
};


struct simpleTask : public task
{
	simpleTask(const std::string& name, const std::string& queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);
	void indicateCreation() override;
	void generateTask(queueContainer& containerLink) override;
	void getSleepTime() override;
	void sleep() override;
	void indicateCompletion();
};