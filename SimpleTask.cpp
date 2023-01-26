#include "SimpleTask.h"
#include "CustomLess.h"

extern  std::vector<std::pair<std::string, std::queue<std::unique_ptr <delayedTask>>>*>* queues;

std::mutex delayedQueueLocker;

simpleTask::simpleTask(std::string name, std::string queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
	: task(name, queue, delayedTaskDelay, simpleTaskDelay,simpleTaskPriority)
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

	consoleLocker.lock();
	for (auto&  element : *queues)
	{
		if (element->first == newQueueName)
		{
			element->second.emplace(std::make_unique<delayedTask>(newName, newQueueName, DelayedTaskDelay, SimpleTaskDelay, SimpleTaskPriority));
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
void simpleTask::getSleepTime()
{
	std::cout << SimpleTaskDelay;
}
void simpleTask::sleep()
{
	std::this_thread::sleep_for(std::chrono::seconds(SimpleTaskDelay));
}