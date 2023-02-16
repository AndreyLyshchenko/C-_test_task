#include "Main.h"
#include "Queue.h"


std::mutex consoleLocker;

int main()
{
	queueContainer queueCont{};
	queueCont.addDelayedQueue("queueD1");
	queueCont.addDelayedQueue("queueD2");
	queueCont.addDelayedQueue("queueD3");
	queueCont.addSimpleQueue("queueS1");

	// All generated threads (and main()) will stuck in infinite loop
	// so no join/detach is needed
	std::thread threadForQueueD1([&]()
		{
			queueCont.generateDelayedTask("taskD1", "queueD1", 10, 2, 1);
		}
	);
	std::thread threadForQueueD2([&]()
		{
			queueCont.generateDelayedTask("taskD2", "queueD2", 10, 2, 2);
		}
	);
	std::thread threadForQueueD3([&]()
		{
			queueCont.generateDelayedTask("taskD3", "queueD3", 10, 2, 1);
		}
	);

	queueCont.executeSimpleTasks("queueS1");

	return 0;
}
