#include "task.h"
#include <cstring>

task::task(std::string name, std::string queue, int delayedTaskDelay, int simpleTaskPriority = 1, int simpleTaskDelay = 2)
	: Name(name), QueueName(queue), DelayedTaskDelay(delayedTaskDelay), SimpleTaskPriority(simpleTaskPriority), SimpleTaskDelay(simpleTaskDelay)
{};

void task::getCurrentTime()
{
	auto timeStamp = std::chrono::system_clock::now();
	std::time_t convertedTimeStamp = std::chrono::system_clock::to_time_t(timeStamp);
	auto noEndlTimeStamp = std::ctime(&convertedTimeStamp);
	auto temp = std::strpbrk(noEndlTimeStamp, "\n");
	if (temp != nullptr)
	{
		*temp = '\0';
	}
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
