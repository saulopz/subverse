#include "Client.h"

Client::Client(string h) : Thread()
{
	sock = 0;
	port = 5000;
	host = h;
}

Client::Client(string h, int p) : Thread()
{
	sock = 0;
	port = p;
	host = h;
}

bool Client::isTerminated()
{
	return (getStatus() == THREAD_STATE_TERMINATED);
}

bool Client::startConnection()
{
	struct sockaddr_in addr;
	struct hostent *hostPtr;

	if ((hostPtr = gethostbyname(host.c_str())) == 0)
	{
		cout << "Error: client cannot interpret host " << host << endl;
		return false;
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
	addr.sin_port = htons((short)port);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		cout << "Error: client cannot create a socket." << endl;
		return false;
	}
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		cout << "Error: client cannot connect to host " << host << endl;
		return false;
	}
	return true;
}

void Client::run()
{
	char msg[1024];
	int message_length = read(sock, msg, sizeof(msg));
	if (message_length == 0)
	{
		cout << "conection with " << host << ":" << sock << " terminated" << endl;
		stop();
	}
	else if (message_length > 0)
	{
		msg[message_length] = '\0';
		message.push_back(msg);
	}
}

int Client::getSock()
{
	return sock;
}

int Client::getPort()
{
	return port;
}

string Client::getHost()
{
	return host;
}

bool Client::sendMessage(string m)
{
	if (!sock)
	{
		return false;
	}
	write(sock, m.c_str(), strlen(m.c_str()));
	return true;
}

string Client::getMessage()
{
	string m = "";
	if (!message.empty())
	{
		m = message[0];
		message.erase(message.begin());
	}
	return m;
}

bool Client::hasMessage()
{
	return (!message.empty());
}

Client::~Client()
{
	stop();
	if (sock)
	{
		close(sock);
	}
}
