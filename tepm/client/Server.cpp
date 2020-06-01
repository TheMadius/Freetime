#include "Server.h"

Server::Server(int port)
{
	flag = true;

	WSAData wsad;
	WORD dll = MAKEWORD(2,1);
	
	if (WSAStartup(dll, &wsad) != 0)
	{
		throw new std::exception("Error, loading dll");
	}

	this->addr.sin_addr.S_un.S_addr = INADDR_ANY;
	this->addr.sin_port = htons(port);
	this->addr.sin_family = AF_INET;
	int size = sizeof(addr);

	this->server = socket(AF_INET, SOCK_STREAM, NULL);

	bind(server, (SOCKADDR*)&addr,sizeof(addr));

	listen(server,SOMAXCONN);

}

void Server::speak(const char* msg)
{
	int size = sizeof(msg);

	send(clients,(char*)&size,sizeof(size),NULL);

	send(clients, msg,sizeof(msg),NULL);

}

char* Server::listenClient(int index)
{
	char* msg;
	int size;

	recv(clients, (char *)&size, sizeof(size), NULL);

	msg = new char[size + 1];

	recv(clients, msg, size, NULL);

	msg[size] = '\0';
	
	return msg;
}

void Server::wait_Client()
{ 
	int size = sizeof(addr);
	
	while (true)
	{
		SOCKET client = accept(this->server, (SOCKADDR*)&addr, &size);

		if (client == 0)
		{
			continue;
		}
		clients = client;
		break;
	}
}

