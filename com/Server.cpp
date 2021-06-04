#include "Server.h"

Server::Server() : Thread()
{
	sock = 0;
	port = 5000;
	error = "";
}

Server::Server(int p) : Thread()
{
	sock = 0;
	port = p;
	error = "";
}

bool Server::startConnection()
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((int)port);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error = "Error: server socket.";
		return false;
	}
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		error = "Error: server bind.";
		return false;
	}
	if (listen(sock, 5) < 0)
	{
		error = "Error: server listen.";
		return false;
	}
	return true;
}

void Server::run()
{
	socklen_t client_addr_size = sizeof(client_addr);
	int client = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size);
	if (client > 0)
	{
		cout << "server: client " << client << " is connected" << endl;
		addClient(client);
	}
}

bool Server::hasNewClient()
{
	return (!client.empty());
}

bool Server::isTerminated()
{
	return (getStatus() == THREAD_STATE_TERMINATED);
}

void Server::addClient(int c)
{
	client.push_back(c);
}

int Server::getClient()
{
	int cli = 0;
	if (!client.empty())
	{
		cli = client[0];
		client.erase(client.begin());
	}
	return cli;
}

int Server::getSocket()
{
	return sock;
}

int Server::getPort()
{
	return port;
}

Server::~Server()
{
	stop();
	if (!client.empty())
	{
		client.clear();
	}
	if (sock)
	{
		close(sock);
	}
}
