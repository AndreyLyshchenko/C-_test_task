#include "Queue.h"
#include "task.h"


task::task(const std::string& name, const std::string& queue, int delayedTaskDelay, int simpleTaskPriority = 1, int simpleTaskDelay = 2)
	: Name(name), QueueName(queue), DelayedTaskDelay(delayedTaskDelay), SimpleTaskPriority(simpleTaskPriority), SimpleTaskDelay(simpleTaskDelay)
{};

bool simpleQueueComparator::operator () (const std::shared_ptr<simpleTask>& left, const std::shared_ptr<simpleTask>& right)
{
	return (left.get()->SimpleTaskPriority > right.get()->SimpleTaskPriority);
}

void task::getCurrentTime()
{
	auto timeStamp = std::chrono::system_clock::now();
	std::time_t convertedTimeStamp = std::chrono::system_clock::to_time_t(timeStamp);
	std::string noEndlTimeStamp(std::ctime(&convertedTimeStamp));
	std::find_if(noEndlTimeStamp.begin(), noEndlTimeStamp.end(),
		[](char& c)->bool
		{
			if (c == '\n')
			{
				c = '\0';
				return true;
			}
			return false;
		}
	);
	std::cout << noEndlTimeStamp;
}
void task::getQueueName()
{
	std::cout << QueueName;
}
void task::getTaskName()
{
	std::cout << Name;
}



simpleTask::simpleTask(const std::string& name,const std::string& queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
	: task(name, queue, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)
{
}
void simpleTask::indicateCreation()
{
	std::lock_guard<std::mutex> consoleLockGuard(consoleLocker);
	getCurrentTime();
	std::cout << " : ";
	getQueueName();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " running..." << std::endl;
}

void simpleTask::generateTask(queueContainer& containerLink)
{
	std::string newName = "taskD";
	newName += (char)Name.back(); // getting  <X> from taskD<X>
	std::string newQueueName = "queueD";
	newQueueName += (char)Name.back();

	std::lock_guard<std::mutex> consoleLockGuard(consoleLocker);
	for (auto& element : containerLink.DelayedQueueContainer)
	{
		if (element->Name == newQueueName)
		{
			element->Queue.emplace(std::make_shared<delayedTask>(newName, newQueueName, DelayedTaskDelay, SimpleTaskDelay, SimpleTaskPriority));
			element->CV.notify_one();
			break;
		}
	}
	this->indicateCompletion();
}

void simpleTask::indicateCompletion()
{
	// Note: console is already protected by lock guard in simpleTask::generateTask();
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

delayedTask::delayedTask(const std::string& name, const std::string& queue, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
	: task(name, queue, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)
{
}

void delayedTask::generateTask(queueContainer& containerLink)
{
	std::string newName = "taskS";
	newName += (char)Name.back(); // getting  <X> from taskD<X>
	std::string newQueueName = "queueS1";

	std::lock_guard<std::mutex> consoleLockGuard(consoleLocker);
	for (auto& element : containerLink.SimpleQueueContainer)
	{
		if (element->Name == newQueueName)
		{
			std::lock_guard<std::mutex> qLockGuard(element->QueueMutex);
			element->Queue.emplace(std::make_shared<simpleTask>(newName, newQueueName, DelayedTaskDelay, SimpleTaskDelay, SimpleTaskPriority));
			element->CV.notify_all();
		}
	}
	this->indicateTaskPush(newName, newQueueName);
}

void delayedTask::indicateCreation()
{
	std::lock_guard<std::mutex> consoleLockGuard(consoleLocker);
	getCurrentTime();
	std::cout << " : ";
	getTaskName();
	std::cout << " - ";
	getSleepTime();
	std::cout << " : created." << std::endl;
}

void delayedTask::indicateTaskPush(const std::string& simpleTaskName,const std::string& simpleTaskQueueName)
{
	// Note: console is already protected by lock guard in delayedTask::generateTask();
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