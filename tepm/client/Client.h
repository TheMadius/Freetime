#pragma once
#include <iostream>
#include <vector>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

class Client
{
public:
	Client(const char* addr, int port);

	void speak(const char* msg);

	char* listen();

private:
	SOCKADDR_IN addr;
	SOCKET client;
};


