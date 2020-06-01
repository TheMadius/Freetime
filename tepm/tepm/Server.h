#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

class Server
{
public :
	Server(int port);
	void speak(const char* msg);
	char* listenClient();
	void wait_Client();

private:
	SOCKADDR_IN addr;
	SOCKET server;
	SOCKET clients;
	bool flag;

};

