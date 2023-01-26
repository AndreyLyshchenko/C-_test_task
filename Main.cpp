#include "Main.h"
#include "DelayedTask.h"
#include "SimpleTask.h"
#include "CustomLess.h"

std::mutex queueS1Locker;

typedef std::vector<std::pair<std::string, std::queue<std::unique_ptr <delayedTask>>>*> queueContainer;

std::priority_queue < std::shared_ptr <simpleTask>, std::deque<std::shared_ptr <simpleTask>>, customLess>* queueS1;

queueContainer* queues;

void generateDelayedTask(std::string taskName, std::string queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority, queueContainer &container)
{
	for (auto& element : container)
	{
		if (element->first == queueName)
		{
			element->second.push(std::make_unique<delayedTask>(taskName, queueName, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)); // new Delayed task is created
			while (true) // infinite loop
			{
				if (!element->second.empty())
				{
					auto &temp = element->second.front();
					auto tempPointer =temp.get();
					tempPointer->indicateCreation();
					tempPointer->sleep();
					tempPointer->generateTask();
					element->second.pop();
				}
			}
		}
	}
}

std::mutex consoleLocker;

int main()
{
	auto* delayQueue1 = new std::pair < std::string, std::queue <std::unique_ptr <delayedTask> > >;
	delayQueue1->first = "queueD1";
	auto* delayQueue2 = new std::pair < std::string, std::queue <std::unique_ptr <delayedTask> > >;
	delayQueue2->first = "queueD2";
	auto* delayQueue3 = new std::pair < std::string, std::queue <std::unique_ptr <delayedTask> > >;
	delayQueue3->first = "queueD3";

	queues = new std::vector<decltype(delayQueue1)>;

	queues->push_back(delayQueue1);
	queues->push_back(delayQueue2);
	queues->push_back(delayQueue3);

	queueS1 = new std::priority_queue < std::shared_ptr <simpleTask>, std::deque<std::shared_ptr <simpleTask>>,customLess>;

	
	std::thread threadForQueueD1(generateDelayedTask, "taskD1", "queueD1", 10, 2, 1, std::ref(*queues));
	std::thread threadForQueueD2(generateDelayedTask, "taskD2", "queueD2", 10, 2, 2, std::ref(*queues));
	std::thread threadForQueueD3(generateDelayedTask, "taskD3", "queueD3", 10, 2, 1, std::ref(*queues));

	while (true) // infinite loop
	{
		if (!queueS1->empty())
		{
			queueS1Locker.lock();	

			auto temp = queueS1->top();
			queueS1->pop();

			queueS1Locker.unlock();

			temp->indicateCreation();
			temp->sleep();
			temp->generateTask();
		}
	}

	return 0;
}
