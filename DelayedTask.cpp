#include "DelayedTask.h"
#include "CustomLess.h"
extern std::priority_queue < std::shared_ptr <simpleTask>, std::deque<std::shared_ptr <simpleTask>>, customLess>* queueS1;
extern std::mutex queueS1Locker;

delayedTask::delayedTask(std::string name, std::string queue, int delayedTaskDelay , int simpleTaskDelay, int simpleTaskPriority)
	: task(name, queue, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)
{
}

void delayedTask::generateTask()
{
	std::string newName = "taskS";
	newName += (char)Name.back(); // getting  <X> from taskD<X>
	std::string newQueueName = "queueS1";

	queueS1Locker.lock();

	consoleLocker.lock();
	queueS1->emplace(std::make_shared<simpleTask>(newName, newQueueName, DelayedTaskDelay,SimpleTaskDelay, SimpleTaskPriority));
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

void delayedTask::getSleepTime()
{
	std::cout << DelayedTaskDelay;
}
void delayedTask::sleep()
{
	std::this_thread::sleep_for(std::chrono::seconds(DelayedTaskDelay));
}