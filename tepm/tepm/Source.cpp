#include <iostream>
#include "Server.h"
#include "Client.h"

using namespace std;

void client()
{
	Client cli("127.0.0.1", 1111);
	
	size_t* use_mem;

	use_mem = (size_t *)cli.listen();

	cout << (*use_mem) /(double)(1024*1024*1024);

}

int main()
{
	MEMORYSTATUS theStatus;
	ZeroMemory(&theStatus, sizeof(theStatus));
	theStatus.dwLength = sizeof(theStatus);
	GlobalMemoryStatus(&theStatus);

	thread t(client);

	Server ser(1111);

	ser.wait_Client();

	size_t use_mem = theStatus.dwTotalPhys - theStatus.dwAvailPhys;

	ser.speak((char*)&(use_mem));

	t.join();
}

