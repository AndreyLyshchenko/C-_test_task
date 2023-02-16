#pragma once
#include <string>
#include <queue>
#include <memory>
#include <vector>
#include <cstring>
#include <condition_variable>

struct baseTask;
struct simpleTask;
struct delayedTask;


using delayQ = std::queue <std::shared_ptr<delayedTask>>;

struct queueContainer;

struct simpleQueueComparator
{
    bool operator () (const std::shared_ptr<simpleTask>& left, const std::shared_ptr<simpleTask>& right);
};

using simpleQ = std::priority_queue<std::shared_ptr<simpleTask>, std::deque<std::shared_ptr<simpleTask>>, simpleQueueComparator>;

struct baseQueue
{
    std::string Name;
    std::mutex QueueMutex;
    std::condition_variable CV;

    template <typename QueueType, typename TaskType>
    void executeTask(QueueType& queueLink, queueContainer& containerLink);

    baseQueue(std::string name)
        :Name(name)
    {}
};

struct delayQueue : baseQueue
{
    delayQ Queue;

    void insertTask(const std::string& taskName,const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);

    delayQueue(const std::string& name)
        :baseQueue(name)
    {  
    }
};

struct simpleQueue : baseQueue
{
    simpleQ Queue;

   simpleQueue(const std::string& name)
        : baseQueue(name)
   {
   }
   void insertTask(const std::string& taskName,const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);
};

std::shared_ptr<delayedTask>& getElement(delayQ& qPointer);
const std::shared_ptr<simpleTask>& getElement(simpleQ& qPointer);

template <typename QueueType, typename TaskType>
void baseQueue::executeTask(QueueType& queueLink, queueContainer& containerLink)
{
    while (true) // infinite loop
    {
        std::shared_ptr<TaskType> temp;
        {
            std::unique_lock<std::mutex> queueUniqueLock(QueueMutex);
            CV.wait(queueUniqueLock, [&]()->bool
                {
                    return !queueLink.empty();
                }
            );
            temp = getElement(queueLink);
            queueLink.pop();
        }
        temp->indicateCreation();

        temp->sleep();
        temp->generateTask(containerLink);
    }
}

struct queueContainer
{
    std::vector<std::shared_ptr<delayQueue>> DelayedQueueContainer;
    std::vector<std::shared_ptr<simpleQueue>> SimpleQueueContainer;
    
    void addSimpleQueue(const std::string& name);
    void addDelayedQueue(const std::string& name);

    void generateDelayedTask(const std::string& taskName, const std::string& queueName, int delayedTaskDelay, int simpleTaskDelay, int simpleTaskPriority);
    void executeSimpleTasks(const std::string& simpleQueueName);
};