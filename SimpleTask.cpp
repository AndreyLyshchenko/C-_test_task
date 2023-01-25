#include "SimpleTask.h"
#include "CustomLess.h"

extern  std::vector<std::pair<std::string, std::queue<std::unique_ptr <delayedTask>>>*>* queues;

std::mutex delayedQueueLocker;

simpleTask::simpleTask(std::string name, std::string queue, int delay, int priority)
	: Priority(priority), task(name, queue, delay)
{
}

void simpleTask::indicateCreation()
{
	consoleLocker.lock();

	getCurrentTime();
	std::cout << " : ";
	getQueueName();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " running..." << std::endl;

	consoleLocker.unlock();
}

void simpleTask::generateTask()
{
	std::string newName = "taskD";
	newName += (char)Name.back(); // getting  <X> from taskD<X>
	std::string newQueueName = "queueD";
	newQueueName += (char)Name.back();
	int newDelay = 10;

	consoleLocker.lock();
	for (auto&  element : *queues)
	{
		if (element->first == newQueueName)
		{
			element->second.emplace(std::make_unique<delayedTask>(newName, newQueueName, newDelay));
			break;
		}
	}
	indicateCompletion();
	consoleLocker.unlock();
}

void simpleTask :: indicateCompletion()
{
	getCurrentTime();
	std::cout << " : ";
	getQueueName();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " completed" << std::endl;
}

simpleTask& simpleTask::operator = (const simpleTask& task)
{
	this->Name = task.Name;
	this->QueueName = task.QueueName;
	this->Priority = task.Priority;
	this->Delay = task.Delay;

	return *this;
}