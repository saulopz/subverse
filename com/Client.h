#ifndef CLIENT_H
#define CLIENT_H

#include "Config.h"
#include "Thread.h"

class Client : public Thread
{
private:
	int sock;
	int port;
	string host;
	string error;
	vector<string> message;

public:
	Client(string);
	Client(string, int);
	int getSock();
	int getPort();
	string getHost();
	bool startConnection();
	virtual void run();
	bool sendMessage(string);
	bool isTerminated();
	string getMessage();
	bool hasMessage();
	virtual ~Client();
};

#endif /* CLIENT_H */
