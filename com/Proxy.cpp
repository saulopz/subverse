#include "Proxy.h"

void *proxyThread(void *arg);

Proxy::Proxy(int s) : Thread()
{
	sock = s;
	start();
}

int Proxy::getSock()
{
	return sock;
}

void Proxy::run()
{
	char msg[1024];
	int message_length = read(sock, msg, sizeof(msg));
	if (message_length == 0)
	{
		cout << "conection " << sock << " terminated" << endl;
		stop();
	}
	else if (message_length > 0)
	{
		msg[message_length] = '\0';
		message.push_back(msg);
	}
}

bool Proxy::sendMessage(string m)
{
	if (!sock)
	{
		return false;
	}
	write(sock, m.c_str(), strlen(m.c_str()));
	return true;
}

string Proxy::getMessage()
{
	string m = "";
	if (!message.empty())
	{
		m = message[0];
		message.erase(message.begin());
	}
	return m;
}

bool Proxy::hasMessage()
{
	return (!message.empty());
}

bool Proxy::isTerminated()
{
	return (getStatus() == THREAD_STATE_STOPED);
}

Proxy::~Proxy()
{
	stop();
	if (sock)
	{
		close(sock);
	}
}
