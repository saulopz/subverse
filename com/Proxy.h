#ifndef PROXY_H
#define PROXY_H

#include "Config.h"
#include "Thread.h"

class Proxy : public Thread
{
private:
	int sock;
	vector<string> message;

public:
	Proxy(int s);
	int getSock();
	bool isTerminated();
	bool sendMessage(string);
	string getMessage();
	bool hasMessage();
	virtual void run();
	virtual ~Proxy();
};

#endif /* PROXY_H */
