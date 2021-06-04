#ifndef SERVER_H
#define SERVER_H

#include "Config.h"
#include "Thread.h"

class Server : public Thread
{
private:
	int sock;
	int port;
	string error;
	vector<int> client;
	struct sockaddr_in client_addr;

public:
	Server();
	Server(int port);
	bool startConnection();
	virtual void run();
	int getPort();
	int getSocket();
	int getClient();
	void addClient(int c);
	bool hasNewClient();
	bool isTerminated();
	virtual ~Server();
};

#endif /* SERVER_H */
