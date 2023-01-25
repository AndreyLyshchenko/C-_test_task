#include "task.h"
#include <string>
#include <thread>


task::task(std::string name, std::string queue, int delay)
	: Name(name), QueueName(queue), Delay(delay)
{};

void task::getCurrentTime()
{
	auto timeStamp = std::chrono::system_clock::now();
	std::time_t convertedTimeStamp = std::chrono::system_clock::to_time_t(timeStamp);
	auto noEndlTimeStamp = std::ctime(&convertedTimeStamp);
	*(noEndlTimeStamp + sizeof(noEndlTimeStamp)*3) = '\0';
	std::cout << noEndlTimeStamp;
}
void task::sleep()
{
	std::this_thread::sleep_for(std::chrono::seconds(Delay));
}
void task::getSleepTime()
{
	std::cout << Delay;
}
void task::getQueueName()
{
	std::cout << QueueName;
}
void task::getTaskName()
{
	std::cout << Name;
}
