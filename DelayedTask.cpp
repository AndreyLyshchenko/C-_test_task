#include "DelayedTask.h"
#include "CustomLess.h"
extern std::priority_queue < std::unique_ptr <simpleTask>, std::deque<std::unique_ptr <simpleTask>>, customLess>* queueS1;
extern std::mutex queueS1Locker;

delayedTask::delayedTask(std::string name, std::string queue, int delay)
	: task(name, queue, delay)
{
}

void delayedTask::generateTask()
{
	std::string newName = "taskS";
	newName += (char)Name.back(); // getting  <X> from taskD<X>
	std::string newQueueName = "queueS1";
	int newDelay = 2;

	int priority;	
	if ((char)Name.back() == '2')
	{
		priority = 2;
	}
	else priority = 1;

	queueS1Locker.lock();

	consoleLocker.lock();
	queueS1->emplace(std::make_unique<simpleTask>(newName, newQueueName, newDelay, priority));
	queueS1Locker.unlock();

	indicateTaskPush(newName, newQueueName);
	consoleLocker.unlock();
}

void delayedTask::indicateCreation()
{
	consoleLocker.lock();

	getCurrentTime();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " : created." << std::endl;

	consoleLocker.unlock();
}

void delayedTask::indicateTaskPush(std::string simpleTaskName, std::string simpleTaskQueueName)
{
	getCurrentTime();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " : (" << simpleTaskName << " : " << simpleTaskQueueName << ") pushed" << std::endl;
}