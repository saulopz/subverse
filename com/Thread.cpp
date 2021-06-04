#include "Thread.h"

void *startThread(void *arg)
{
	Thread *thread = (Thread *)arg;
	while (thread->getStatus() == THREAD_STATE_RUNNING)
	{
		thread->run();
	}
	return NULL;
}

Thread::Thread()
{
	id = 0;
	status = THREAD_STATE_STOPED;
}

void Thread::run()
{
}

bool Thread::start()
{
	status = THREAD_STATE_RUNNING;
	if (pthread_create(&id, NULL, startThread, (void *)this))
	{
		return false;
		cout << "not started" << endl;
	}
	return true;
}

void Thread::stop()
{
	status = THREAD_STATE_STOPED;
	if (id)
	{
		pthread_join(id, NULL);
	}
}

int Thread::getStatus()
{
	return status;
}

Thread::~Thread()
{
	stop();
}
