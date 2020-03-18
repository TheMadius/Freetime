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
	Server(const char *addr, int port);

	void speak(const char* msg,int index);

	char* listenClient(int index);

	void wait_Client();
	int getCount();

private:
	SOCKADDR_IN addr;
	SOCKET server;
	vector<SOCKET> clients;
	mutex m,m2;
	condition_variable Cv;
	bool flag;

};

