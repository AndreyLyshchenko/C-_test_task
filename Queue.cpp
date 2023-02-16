#include "Queue.h"
#include "task.h"



void delayQueue::insertTask(const std::string& taskName,const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
{
	Queue.push(std::make_shared<delayedTask>(taskName, queueName, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)); // new Delayed task is created
}

void simpleQueue::insertTask(const std::string& taskName,const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
{
	Queue.push(std::make_shared<simpleTask>(taskName, queueName, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority)); // new Simple task is created
}

void queueContainer::addSimpleQueue(const std::string& name)
{
	SimpleQueueContainer.push_back(std::make_shared<simpleQueue>(name));
}
void queueContainer::addDelayedQueue(const std::string& name)
{
	DelayedQueueContainer.push_back(std::make_shared<delayQueue>(name));
}

void queueContainer::generateDelayedTask(const std::string& taskName, const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority)
{
	for (auto& element : DelayedQueueContainer)
	{
		if (element->Name == queueName)
		{
			element->insertTask(taskName, queueName, delayedTaskDelay, simpleTaskDelay, simpleTaskPriority);
			element->executeTask<delayQ, delayedTask>(element->Queue, *this);
		}
	}
}

void queueContainer::executeSimpleTasks(const std::string& simpleQueueName)
{
	for (auto& element : SimpleQueueContainer)
	{
		if (element->Name == simpleQueueName)
		{
			element->executeTask<simpleQ, simpleTask>(element->Queue, *this);
		}
	}
}

std::shared_ptr<delayedTask>& getElement(delayQ& qPointer)
{
	return qPointer.back();
};
const std::shared_ptr<simpleTask>& getElement(simpleQ& qPointer)
{
	return qPointer.top();
};