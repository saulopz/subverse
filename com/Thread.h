#ifndef THREAD_H
#define THREAD_H

#include "Config.h"
#include <pthread.h>

#define THREAD_STATE_STOPED 0
#define THREAD_STATE_RUNNING 1
#define THREAD_STATE_TERMINATED 2

class Thread
{
private:
	pthread_t id;
	int status;

public:
	Thread();
	int getId();
	int getStatus();
	bool start();
	void stop();
	virtual void run();
	virtual ~Thread();
};

#endif /* THREAD_H */
