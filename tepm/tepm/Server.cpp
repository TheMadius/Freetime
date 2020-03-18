#include "Server.h"

Server::Server(const char* ip, int port)
{
	flag = true;

	WSAData wsad;
	WORD dll = MAKEWORD(2,1);
	
	if (WSAStartup(dll, &wsad) != 0)
	{
		throw new std::exception("Error, loading dll");
	}

	this->addr.sin_addr.S_un.S_addr = inet_addr(ip);
	this->addr.sin_port = htons(port);
	this->addr.sin_family = AF_INET;
	int size = sizeof(addr);

	this->server = socket(AF_INET, SOCK_STREAM, NULL);

	bind(server, (SOCKADDR*)&addr,sizeof(addr));

	listen(server,SOMAXCONN);
	
	thread wait([&]() {
		wait_Client();
		});

	wait.detach();
}

void Server::speak(const char* msg, int index)
{
	int size = sizeof(msg);

	unique_lock<mutex> loc(m2);
	this->Cv.wait(loc, [&]() {return ((index + 1) <= this->getCount()); });

	m.lock();

	send(clients[index],(char*)&size,sizeof(size),NULL);

	send(clients[index], msg,sizeof(msg),NULL);

	m.unlock();
}

char* Server::listenClient(int index)
{
	char* msg;
	int size;

	unique_lock<mutex> loc(m2);
	cout << "lo2";
	this->Cv.wait(loc, [&]() {return ((index + 1) <= this->getCount()); });

	m.lock();
	recv(clients[index], (char *)&size, sizeof(size), NULL);
	m.unlock();

	msg = new char[size + 1];

	m.lock();
	recv(clients[index], msg, size, NULL);
	m.unlock();

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
		cout << "lo";
			continue;
		}

		m.lock();
		clients.push_back(client);
		Cv.notify_one();
		m.unlock();

	}
}

int Server::getCount()
{
	return this->clients.size();
}

