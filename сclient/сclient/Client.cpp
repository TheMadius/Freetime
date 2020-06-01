#include "Client.h"

Client::Client(const char* ip, int port)
{
	WSAData wsad;
	WORD dll = MAKEWORD(2, 1);

	if (WSAStartup(dll, &wsad) != 0)
	{
		throw new std::exception("Error, loading dll");
	}

	this->addr.sin_addr.S_un.S_addr = inet_addr(ip);
	this->addr.sin_port = htons(port);
	this->addr.sin_family = AF_INET;
	int size = sizeof(addr);

	this->client = socket(AF_INET, SOCK_STREAM, NULL);

}

void Client::connectSrev()
{
	int size = sizeof(addr);
	while (true)
	{
		int res = connect(client, (SOCKADDR*)&addr, size);

		if (res != 0)
		{
			continue;
		}
		break;
	}
}

void Client::speak(const char* msg)
{
	int size = sizeof(msg);

	send(this->client, (char*)&size, sizeof(size), NULL);

	send(client, msg, sizeof(msg), NULL);
}

char* Client::listen()
{
	char* msg;
	int size;

	recv(client, (char*)&size, sizeof(size), NULL);

	msg = new char[size + 1];

	recv(client, msg, size, NULL);

	msg[size] = '\0';

	return msg;
}
